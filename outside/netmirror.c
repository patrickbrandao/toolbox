//				a
//		s

/**
    Handle multiple socket connections with select and fd_set on Linux
*/
  
#include <stdio.h>
#include <string.h>   //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <signal.h> // sigaction(), sigsuspend(), sig*()
#include <fcntl.h>
#include <netdb.h>
#include <net/if.h> 

#define NETMIRROR_MAXCONN 1024
#define NETMIRROR_MAXFD   64
#define BUFFER_SIZE 1024
#define BUFFER_MAXSIZE 16384
#define NETMIRROR_FERROR(strErr, errNo)		{ fprintf(stderr, strErr); exit(errNo); }

// VARIAVEIS GLOBAIS
pid_t pid;

void help_netmirror(){
	printf("Use: netmirror [opcoes]\n");
	printf("Opcoes:\n");
	printf(" -c SERVER      : MODO CLIENTE, especificar IPv4 ou IPv6 do servidor\n");
	printf(" -i DEV         : MODO CLIENTE, definir interface de saida\n");
	printf(" -p PORT        : Numero da porta, padrao 7000\n");
	printf(" -a N           : Fator de amplificacao dos dados recebidos\n");
	printf(" -r N           : Replicar sempre rajada de N bytes\n");
	printf(" -m MSS         : Especificar o MSS da transmissao\n");
	printf(" -S IP-Size     : Especificar o tamanho do pacote IP\n");
	printf(" -C N           : Especificar caracter fixo nos bytes da resposta (ascii)\n");
	printf(" -f             : Rodar em loop infinito\n");
	printf(" -F             : Rodar em modo foreground (padrao no modo cliente)\n");
	printf(" -D             : Rodar em modo background (padrao no modo servidor)\n");

	printf(" -4             : Rodar em IPv4 (padrao)\n");
	printf(" -6             : Rodar em IPv6\n");
	printf(" -x             : Ativar debug\n");
	printf("\n");
	exit(1);
}

// Modo background/foreground
void daemonize(){
	pid = fork();
	if (pid == -1) NETMIRROR_FERROR("Falha ao enviar para background (fork)\n", 79);
	
	// processo pai morre e deixa pra la.
	if (pid != 0) exit(0);

	// Filho 1
	// become session leader
	if (setsid() < 0) exit(51);

	signal(SIGHUP, SIG_IGN);

	// Filho 2
	pid = fork();
	if ( pid < 0){
		// Falha ao criar filho 2
		exit(52);
	}else if (pid){
		// Encerrar Filho 1
		exit(0);
	}
	// Redirecionar STDIN, STDOUT, STDERR para null
	open("/dev/null", O_RDONLY);
	open("/dev/null", O_RDWR);
	open("/dev/null", O_RDWR);			

}

// Definir MSS de um socket
void tcp_socket_set_mss(unsigned int set_mss, int target_socket){
	if(!set_mss || set_mss < 128) return; // MSS invalido
	// Definir MSS
	setsockopt(target_socket, IPPROTO_TCP, TCP_MAXSEG, &set_mss, sizeof(set_mss) );
}

// Ler string e determinar se e' ipv4 ou ipv6
int read_remote_addr(char* input, int *remote_port){
	int af = -1;
	int len = 0;
	int idx = 0;
	int i;
	int cc = 0;
	int cd = 0;
	char addr[200];
	char port[6];
	int port_number = 0;
	int ai_family = -1;
	struct in_addr ipv4;

	memset(&addr, 0, 200);
	memset(&port, 0, 6);

	len = strlen(input);
	if(!len || len > 190) return ai_family;

	if(input[idx]=='['){
		// ipv6 com notacao
		ai_family = 6;

		// notacao ipv6
		idx++;
		for(i=idx;i<len;i++){
			char m;
			m=input[i];
			idx=i;
			if(!m) break;
			if(m==']'){
				// avancar para depois da notacao e parar
				idx++;
				break;
			}
			addr[i-1] = m;
		}
	
	}else{
		// ipv6 ou ipv4
		for(i=0;i<len;i++){
			char m;
			m=input[i];
			idx=i;
			if(!m) break;

			// contagem de pontos indica ipv4
			if(m=='.') cd++;

			// contagem de : indica ipv6 ou separacao ipv4:porta
			if(m==':'){
				cc++;
				if(!cd){
					// : sem pontos anteriores, indica familia ipv6
					ai_family = 6;
				}else{
					// pontos encontrados, seguidos de :, familia ipv4
					ai_family = 4;
					
					// parar
					break;
				}
			}
			addr[i] = m;
		}
	}
	// se nao for IPv6 e 3 pontos foram encontrados, temos um IPv4
	if(ai_family < 0 && cd == 3) ai_family = 4;

	// ler porta
	if(idx<len){
		int j = 0;
		for(i=idx; i<len && j < 5;i++){
			char m;
			m=input[i];
			if(m==':') continue;
			if(m >= 48 && m <= 57) port[j++] = m;
		}	
	}

	// Porta obtida, exportar
	*remote_port = atoi(port);

	// printf(" --> FAMILY: %d INPUT: %s ADDR: %s PORT: %s PORT NUMBER: %d\n", ai_family, input, addr, port, port_number);

	return ai_family;
}

// int main_netmirror(const char *progname, const int argc, const char **argv){
int main(int argc , char *argv[]){
	// Opcoes:
	int netmirror_sport = 7000;				// Numero da porta
	int netmirror_amplificate = 0;			// Fator de multiplicacao dos dados
	int netmirror_requestdata = 0;			// Quantida de dados a serem enviados por mensagem (modo rajada)
	unsigned int netmirror_mss = 0;					// Especificar MSS
	int netmirror_ifixedchar = 0;			// Caracter fixo de resposta
	int netmirror_flood = 0;				// Enviar flood apos conectar
	int netmirror_protocol = 4;				// Protocolo: 4=ipv4, 6=ipv6
	int netmirror_ipsize = 0;				// Tamanho do pacote IP
	int netmirror_daemon = -1;				// Modo daemon, -1=automatico (server=1, client=0), 0=desativa, 1=ativa
	int netmirror_debug = 0;				// Ativar depuracao
	unsigned char netmirror_fixedchar = 65;

	// contador de bytes
	int rxcount = 0;
	int txcount = 0;

	int sock_opt = 1;
	int master_socket , addrlen , new_socket , client_socket[NETMIRROR_MAXCONN] , max_clients = NETMIRROR_MAXCONN , activity, i , valread , sockdesc;
	int sindex = 0;
	int max_sd;
	struct sockaddr_in address4;
	struct sockaddr_in6 address6;

	// Modo Cliente
	int client_mode = 0;					// 0=modo servidor, 4=modo cliente ipv4, 6=modo cliente ipv6
	char server_address[INET6_ADDRSTRLEN];	// IPv4 ou IPv6 do servidor
	struct hostent *server;					// Dados do lado servidor
	char *local_interface = NULL;			// Associar na interface

	// String para armazenar IP remoto convertido (modo servidor, IP do cliente)
	char client_str[INET6_ADDRSTRLEN];

	// Processamento de argumentos
	int opt;
	char *options = "p:a:r:m:S:c:C:i:DF46xfh";
	unsigned char chrflood = 0;

	// Buffer fixo
	unsigned char* data_buffer = NULL;
	int data_len = 0;

	// Buffer de trabalho
	char buffer[BUFFER_MAXSIZE];
	bzero(&buffer, BUFFER_MAXSIZE);

	//set of socket descriptors
	fd_set readfds;

	//a message
	//-char *message = "ECHO Daemon v1.0 \r\n";

	//initialise all client_socket[] to 0 so not checked
	for (sindex = 0; sindex < max_clients; sindex++) {
		client_socket[sindex] = 0;
	}
	sindex = 0;

	//----------------------------------------- Processar argumentos

	// Processar argumentos
	while((opt = getopt(argc, argv, options)) != -1) {
		switch(opt) {
			// Forcar modo foreground
			case 'F': netmirror_daemon = 0; break;
			// Forcar modo background
			case 'D': netmirror_daemon = 1; break;

			// Modo cliente, IP do servidor remoto
			case 'c':
				bzero(server_address, INET6_ADDRSTRLEN);
				if (sscanf(optarg, "%s", server_address) != 1) NETMIRROR_FERROR("Erro ao processar argumento do IP do servidor remoto\n", 21);

				// Ler IP remoto (e porta remota se presente)
				client_mode = read_remote_addr(server_address, &netmirror_sport);
				if(client_mode < 0) NETMIRROR_FERROR("Erro ao processar argumento do IP do servidor remoto, informe um IPv4 ou IPv6\n", 22);

			// Interface de saida
			case 'i':
				local_interface = NULL;
				if (sscanf(optarg, "%s", local_interface) != 1) NETMIRROR_FERROR("Erro ao processar argumento de interface\n", 25);
				break;

			// Porta
			case 'p':
				// Fator de amplificacao
				netmirror_sport = 7000;
				if (sscanf(optarg, "%d", &netmirror_sport) != 1) NETMIRROR_FERROR("Erro ao processar argumento do cluster ID\n", 31);
				if(netmirror_sport < 0 || netmirror_sport > 65535) NETMIRROR_FERROR("Numero de porta invalida\n", 32);
				break;

			// Adicionar instancia
			case 'a':
				// Fator de amplificacao
				netmirror_amplificate = 0;
				if (sscanf(optarg, "%d", &netmirror_amplificate) != 1) NETMIRROR_FERROR("Erro ao processar argumento do cluster ID\n", 41);
				if(netmirror_amplificate < 1) NETMIRROR_FERROR("Numero de amplificacao invalido\n", 42);
				break;

			// Rajada fixa
			case 'r':
				netmirror_requestdata = 0;
				if (sscanf(optarg, "%d", &netmirror_requestdata) != 1) NETMIRROR_FERROR("Erro ao processar argumento do rajada fixa\n", 51);
				if(netmirror_requestdata < 1) NETMIRROR_FERROR("Numero de rejada invalido\n", 52);
				break;

			// MSS
			case 'm':
				netmirror_mss = 0;
				if (sscanf(optarg, "%d", &netmirror_mss) != 1) NETMIRROR_FERROR("Erro ao processar argumento MSS\n", 51);
				if(netmirror_mss < 64 || netmirror_mss > 16330) NETMIRROR_FERROR("Numero de MSS invalido [64-16330]\n", 52);
				break;

			// Pacote IP
			case 'S':
				netmirror_ipsize = 0;
				if (sscanf(optarg, "%d", &netmirror_ipsize) != 1) NETMIRROR_FERROR("Erro ao processar argumento IP-Size\n", 51);
				if(netmirror_ipsize < 128 || netmirror_ipsize > 16384) NETMIRROR_FERROR("Numero de IP-Size invalido [128-16384]\n", 52);
				break;

			// FIXED CHAR
			case 'C':
				netmirror_ifixedchar = 0;
				if (sscanf(optarg, "%d", &netmirror_ifixedchar) != 1) NETMIRROR_FERROR("Erro ao processar argumento de caracter fixo\n", 61);
				if(netmirror_ifixedchar < 0 || netmirror_ifixedchar > 255) NETMIRROR_FERROR("Numero de caracter ASCII invalido\n", 62);
				netmirror_fixedchar = (unsigned char)(netmirror_ifixedchar);
				break;

			// Protocolo IP
			case '4': netmirror_protocol = 4; break;
			case '6': netmirror_protocol = 6; break;

			// Debug
			case 'x':
				netmirror_debug++;
				break;

			// Flood
			case 'f':
				netmirror_flood = 1;
				break;

			// Ajuda
			case 'h':
				help_netmirror();
				break;


		} // switch
	} // while

	// Criticas
	// - Sem nenhuma ainda

	// Background:
	if(netmirror_daemon < 0) netmirror_daemon = (client_mode ? 0 : 1);

	// Adaptacoes
	// - Preencher caracter do buffer inicial
	for(i = 0; i < BUFFER_MAXSIZE - 1; i++ ) buffer[i] = netmirror_fixedchar;

	// Buffer requisitado
	// - em modo cliente, precisa ter o buffer de upload
	if(client_mode && !netmirror_requestdata) netmirror_requestdata = (1024*16);
	if(netmirror_requestdata){
		data_buffer = malloc(netmirror_requestdata * sizeof(unsigned char) + 1);
		bzero(data_buffer, netmirror_requestdata + 1);
		// Preencher com caracter
		for(i = 0; i < netmirror_requestdata; i++) data_buffer[i] = netmirror_fixedchar;
	}

	// Amplificacao no eco
	if(netmirror_amplificate < 1) netmirror_amplificate = 1;

	// Definir MSS
	if(netmirror_ipsize){
		// cabecalho ipv4: 54 bytes
		// cabecalho ipv6: 80 bytes
		netmirror_mss = (netmirror_protocol==4) ? netmirror_ipsize - 54 : netmirror_ipsize - 80;
	}

	// Depurar
	if(netmirror_debug){
		printf(" [!] [DEBUG]\n");
		printf(" [!]    server_address...........: %s\n", server_address);
		printf(" [!]    local_interface..........: %s\n", local_interface);
		printf(" [!]    netmirror_sport..........: %d\n", netmirror_sport);
		printf(" [!]    netmirror_amplificate....: %d\n", netmirror_amplificate);
		printf(" [!]    netmirror_requestdata....: %d\n", netmirror_requestdata);
		printf(" [!]    netmirror_mss............: %d\n", netmirror_mss);
		printf(" [!]    netmirror_ifixedchar.....: %d\n", netmirror_ifixedchar);
		printf(" [!]    netmirror_flood..........: %d\n", netmirror_flood);
		printf(" [!]    netmirror_protocol.......: %d\n", netmirror_protocol);
		printf(" [!]    netmirror_ipsize.........: %d\n", netmirror_ipsize);
		printf(" [!]    netmirror_debug..........: %d\n", netmirror_debug);
		printf(" [!]    netmirror_fixedchar......: [%c]\n", netmirror_fixedchar);
	}

	//----------------------------------------- ECHO CLIENT

	if(client_mode){
		struct ifreq ifr;

		// data_buffer / netmirror_requestdata

		// Modo daemon ou modo foreground
		if(netmirror_daemon) daemonize();

		// socket: create the socket
		master_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (master_socket < 0) NETMIRROR_FERROR("Erro ao abrir client-socket\n", 100);

		// Associar interface local
		if(local_interface){
			memset(&ifr, 0, sizeof(ifr));
			snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), local_interface);
			if (setsockopt(master_socket, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0)
				NETMIRROR_FERROR("Erro ao associar interafce de saida\n", 102);
			//-
		}

		// gethostbyname: get the server's DNS entry
		server = gethostbyname(server_address);
		if (server == NULL) NETMIRROR_FERROR("Erro ao abrir resolver gethostbyname()\n", 102);

		// build the server's Internet address
		bzero((char *) &address4, sizeof(address4));
		address4.sin_family = AF_INET;
		bcopy((char *)server->h_addr, (char *)&address4.sin_addr.s_addr, server->h_length);
		address4.sin_port = htons(netmirror_sport);

		// connect: create a connection with the server
		if (connect(master_socket, (const struct sockaddr *) & address4, sizeof(address4)) < 0) NETMIRROR_FERROR("Erro ao abrir conexao com servidor remoto\n", 103);

		// Enviar buffer padrao para o servidor
		do{

			if(netmirror_debug) printf(" [+] Enviando %d bytes\n", netmirror_requestdata);
			txcount = write(master_socket, data_buffer, netmirror_requestdata);
			if (txcount < 0) NETMIRROR_FERROR("Erro ao enviar dados para o servidor remoto\n", 104);
			//if (txcount != netmirror_requestdata) NETMIRROR_FERROR("Erro durante envio de dados para o servidor remoto\n", 104);

			// Receber dados do servidor
			bzero(buffer, BUFFER_MAXSIZE);
			if(netmirror_debug) printf(" [.] Iniciando leitura, buffer de %d bytes\n", BUFFER_MAXSIZE);
			rxcount = read(master_socket, buffer, BUFFER_MAXSIZE);
			if (rxcount < 0) NETMIRROR_FERROR("Erro, dados enviados porem houve erros na leitura\n", 105);

			// nao importa o que o servidor respondeu!
			//printf("Echo from server: %s", buffer);
			if(netmirror_debug) printf(" [!] Echo from server: %d bytes\n", rxcount);

		} while(netmirror_flood);

		close(master_socket);

		// Fim.
		return 0;
	}

	//----------------------------------------- ECHO SERVER SINGLE INSTANCE

	// Criar SOCKET
	if( (master_socket = socket(netmirror_protocol == 4 ? AF_INET : AF_INET6 , SOCK_STREAM , 0)) == 0) {
		perror("socket failed");
		NETMIRROR_FERROR("Erro ao abrir socket\n", 11);
		exit(EXIT_FAILURE);
	}

	// Definir suporte a mulplicas conexoes reciclaveis
	if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&sock_opt, sizeof(sock_opt)) < 0 ){
		perror("setsockopt");
		NETMIRROR_FERROR("Erro ao definir opcao REUSEADDR no socket\n", 12);
		exit(EXIT_FAILURE);
	}

	// Definir MSS
	if(netmirror_mss){
		tcp_socket_set_mss(netmirror_mss, master_socket);
		if(netmirror_debug) printf(" [>] TCP-MSS Setted: %d\n", netmirror_mss);
	}

	// Parametros de BIND e BIND
	switch(netmirror_protocol){
		case 4:
			// Socket IPv4
			address4.sin_family = AF_INET;
			address4.sin_addr.s_addr = INADDR_ANY;
			address4.sin_port = htons( netmirror_sport );

			// BIND IPv4
			if(netmirror_debug) printf(" [L] Listener on IPv4 port %d \n", netmirror_sport);
			if (bind(master_socket, (struct sockaddr *)&address4, sizeof(address4) )<0){
				perror("bind4 failed");
				NETMIRROR_FERROR("Erro ao dar BIND IPv4 no socket\n", 13);
				exit(EXIT_FAILURE);
			}
			break;

		case 6:
			// Socket IPv6
			address6.sin6_flowinfo = 0;
			address6.sin6_port = htons( netmirror_sport );
			address6.sin6_family = AF_INET6;

			// BIND IPv6
			if(netmirror_debug) printf(" [L] Listener on IPv6 port %d \n", netmirror_sport);
			if (bind(master_socket, (struct sockaddr *) &address6, sizeof(address6) )<0){
				perror("bind6 failed");
				NETMIRROR_FERROR("Erro ao dar BIND IPv6 no socket\n", 14);
				exit(EXIT_FAILURE);
			}
			break;
	}

	// Especificar o maximo de conexoes pendentes no socket principal
	if (listen(master_socket, 3) < 0){
		perror("listen");
		NETMIRROR_FERROR("Erro ao dar LISTEN no socket\n", 15);
		exit(EXIT_FAILURE);
	}


	//----------------------------------------- FORK to daemon

	if(netmirror_daemon) daemonize();

	//----------------------------------------- Pronto para atender!


	// Tamanho do endereco
	addrlen = (netmirror_protocol == 4) ? sizeof(address4) : sizeof(address6);

	//accept the incoming connection
	if(netmirror_debug) printf(" [W] Waiting for connections ...\n");
	 
	while(1) {
		//clear the socket set
		FD_ZERO(&readfds);

		//add master socket to set
		FD_SET(master_socket, &readfds);
		max_sd = master_socket;
		 
		//add child sockets to set
		for ( sindex = 0 ; sindex < max_clients ; sindex++) {
			//socket descriptor
			sockdesc = client_socket[sindex];
		     
			//if valid socket descriptor then add to read list
			if(sockdesc > 0) FD_SET( sockdesc , &readfds);
		    
			//highest file descriptor number, need it for the select function
			if(sockdesc > max_sd) max_sd = sockdesc;
		}

		//wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

		//-if ((activity < 0) && (errno!=EINTR)) {
		    //-printf("select error");
		//-}
		  
		//If something happened on the master socket , then its an incoming connection
		if (FD_ISSET(master_socket, &readfds)){

			// Aguardar nova conexao
			new_socket = (netmirror_protocol == 4) ?
					accept(master_socket, (struct sockaddr *)&address4, (socklen_t*)&addrlen)
				:
					accept(master_socket, (struct sockaddr *)&address6, (socklen_t*)&addrlen) ;
			//-

			// Falha ao receber nova conexao
			if ( new_socket  < 0 ){
				perror("accept");
				exit(EXIT_FAILURE);
			}

			// Definir MSS novamente
			tcp_socket_set_mss(netmirror_mss, new_socket);

			//inform user of socket number - used in send and receive commands
			if(netmirror_debug){
				bzero(client_str, INET6_ADDRSTRLEN);

				if(netmirror_protocol == 4){
					inet_ntop(AF_INET, &(address4.sin_addr), client_str, INET_ADDRSTRLEN);
					printf(" [N] New IPv4 connection, socket %d, IPv4: [%s] src-port: %d\n", new_socket, client_str, ntohs(address4.sin_port));
				}else{
					inet_ntop(AF_INET6, &(address6.sin6_addr), client_str, INET6_ADDRSTRLEN);
					printf(" [N] New IPv6 connection, socket %d, IPv6: [%s] src-port: %d\n", new_socket, client_str, ntohs(address6.sin6_port));
				}
			}

			//send new connection greeting message
			//-if( send(new_socket, message, strlen(message), 0) != strlen(message) ){
			//-    perror("send");
			//-}

			//add new socket to array of sockets
			for (sindex = 0; sindex < max_clients; sindex++) {
				//if position is empty
				if( client_socket[sindex] == 0 ){
					client_socket[sindex] = new_socket;
					if(netmirror_debug) printf(" [A] Adding to list of sockets as %d\n" , sindex);
					break;
				}
			}

			// Flodando cliente
			if(netmirror_flood){
				int blen = 0;
				blen = strlen(buffer);
				for(;;) if( send(new_socket, buffer, blen, 0) != blen ) break;
			}
		}

		//else its some IO operation on some other socket :)
		for (sindex = 0; sindex < max_clients; sindex++){

			sockdesc = client_socket[sindex];

			if (FD_ISSET( sockdesc , &readfds)){

				// Sessao UP

				//Check if it was for closing , and also read the incoming message
				//-if ((valread = read( sockdesc , buffer, 1024)) == 0){
				if ((valread = read( sockdesc , buffer, BUFFER_MAXSIZE)) == 0){

					// Cliente remoto desconectado, obter detalhes
					if(netmirror_debug){
						bzero(client_str, INET6_ADDRSTRLEN);

						if(netmirror_protocol == 4){
							getpeername(sockdesc , (struct sockaddr*)&address4 , (socklen_t*)&addrlen);
							inet_ntop(AF_INET, &(address4.sin_addr), client_str, INET_ADDRSTRLEN);
							if(netmirror_debug) printf(" [X] IPv4 Host disconnected, IPv4 [%s] src-port %d \n", client_str, ntohs(address4.sin_port));
						}else{
							getpeername(sockdesc , (struct sockaddr*)&address6 , (socklen_t*)&addrlen);
							inet_ntop(AF_INET6, &(address6.sin6_addr), client_str, INET6_ADDRSTRLEN);
							if(netmirror_debug) printf(" [X] IPv6 Host disconnected, IPv6 [%s] src-port %d \n", client_str, ntohs(address6.sin6_port));
						}
					}

					// Close the socket and mark as 0 in list for reuse
					close( sockdesc );
					client_socket[sindex] = 0;

				}else{

					// Echo back the message that came in
					// set the string terminating NULL byte on the end of the data read
					buffer[valread] = '\0';
					// modo resposta fixa
					if(netmirror_requestdata){
						rxcount = send(sockdesc , data_buffer , netmirror_requestdata, 0 );
						if(rxcount != netmirror_requestdata){
							// desconectou durante envio
							close( sockdesc );
							client_socket[sindex] = 0;
						}
					}else{
						// modo eco
						for(i=0; i < netmirror_amplificate; i++){
							rxcount = send(sockdesc , buffer , valread , 0 );
							if(rxcount != valread){
								// desconectou durante envio
								close( sockdesc );
								client_socket[sindex] = 0;
							}
						}
					}
				}
		    }
		}
	}

	return 0;

} 










