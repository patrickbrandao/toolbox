#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include <sys/types.h>
#include <sys/param.h>
#include <arpa/inet.h>
#include <ctype.h>

/*
	
	Recebe um ipv4 e retorna qual o ip local usado como ip de origem para enviar pacotes

*/

void help_ipv4srcget(){
	printf("\n");
	printf("ipv4srcget\n");
	printf("Recebe um endereco IPv4, interpreta zeros a esquerda e omissoes e imprime na saida\n");
	printf("\n");
	printf("Use: ipv4srcget [ipv4] [ipv4] [ipv4][...]\n");
	printf("\n");
	exit(1);	
}

int main_ipv4srcget(const char *progname, const int argc, const char **argv){
	int i;
    if(argc!=2) help_ipv4srcget();

    const char * find_ipaddr = argv[1];


	struct sockaddr_in srv_sock;
	int netsocket = socket ( AF_INET, SOCK_DGRAM, 0);
	unsigned char buffer[100];
	unsigned char * ret = NULL;

	// erro ao criar socket para rede
	if(netsocket < 0){
		printf("\n");
		return 8;
	}

	// zerar socket e buffer
	memset( &srv_sock, 0, sizeof(srv_sock) );
	memset( buffer, 0, sizeof(buffer) );

	// configurar
	srv_sock.sin_family = AF_INET;
	srv_sock.sin_port = htons(53);

	// ler string e codificar em decimal 32 bits
	//- srv_sock.sin_addr.s_addr = inet_addr( find_ipaddr );
	srv_sock.sin_addr.s_addr = inet_pton_ng( find_ipaddr );

	// criar tomada de conexao/datagrama
	int err = connect(netsocket, (const struct sockaddr*) &srv_sock, sizeof(srv_sock) );

	struct sockaddr_in name;
	socklen_t namelen = sizeof(name);
	err = getsockname(netsocket, (struct sockaddr*) &name, &namelen);

	const char* p = inet_ntop(AF_INET, &name.sin_addr, buffer, 100);

	// fechar socket, buffer ja foi preenchido!
	close(netsocket);

	// verificar se foi possivel obter o tip de 'name'
	if(p != NULL){
		// obtido com sucesso!
		printf("%s\n", buffer);

	}else{
		// deu erro... falta de gateway ou problemas de rede nao configurada
		printf("\n");
		return 5;
	}
	return 0;
}















