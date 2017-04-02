#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>

#define IS_URL_XOR(A, B)		( (A && !B) || (!A && B) )

void help_is_url(){
	printf("\n");
	printf("is_url\n");
	printf("Verifica se os parametros estao no formato URL\n");
	printf("Retorno stdno=0 em caso de correto ou >0 se estiver incorreto\n");
	printf("\n");
	printf("Exemplos:\n");
	printf("\n");
	printf("\thttp://www.intranet.br\n");
	printf("\thttps://www.intranet.br/\n");
	printf("\tftp://www.intranet.br/\n");
	printf("\thttp://www.intranet.br:8080/?\n");
	printf("\thttp://www.intranet.br/dir1?q=123\n");
	printf("\thttp://www.intranet.br/dir1/file.php?q=123&v=999\n");
	printf("\thttp://www.intranet.br/dir9/dir8/arquivo2.zip\n");
	printf("\thttp://[2804:cafe::beba:c0ca]\n");
	printf("\thttp://[2804:cafe::beba:c0ca]/file.tgz\n");
	printf("\thttps://[2804:cafe:0001:0002:aaaa:bbbb:beba:c0ca]:8081\n");
	printf("\thttps://[2804:cafe:0001:0002:aaaa:bbbb:beba:c0ca]:8081/\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: is_url (URL)\n");
	printf("\n");
	exit(1);
}

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/*

// testar se string esta no formato ipv4
// porta na mesma declaracao
int is_ipv4(const char *str){
	struct in_addr ipv4addr;
	if(!inet_pton(AF_INET, str, &(ipv4addr))) return 1;
	return 0;
}

// testar se string esta no formato FQDN (com ponto)
int is_fqdn(const char *str){
	register int i;
	int test = 0;
	int len = strlen(str);
	int bcount = 0, dcount = 0;
	int have_dot = 0;

	// impossivel ter um nome menor que 3 bytes: x.y
	if(len < 3) return 8;
	// impossivel ter um mac maior que 256 bytes
	if(len > 254) return 9;

	// analise de caracteres
	for(i=0;i<len;i++){
		char ch = str[i];
		char bf = 0;

		// caracter anterior
		if(i) bf = str[i-1];

		// converter para minusculo
		ch = tolower(ch);

		// tem ponto?
		if(ch=='.') have_dot++;

		// caracter proibido
		if(ch != '.' && ch != '-' && !isalnum(ch)) return 7;

		// nao pode comecar com ponto ou traco
		if(!i && (ch=='.'||ch=='-')) return 6;

		// nao pode terminar com traco
		// (pode terminar com ponto, FQDN de dns termina com ponto)
		if(i+1==len && ch=='-') return 5;

		// nao pode ter ponto ou traco duplo
		if( (ch=='.' || ch=='-') && bf == ch ) return 4;

	}

	// sem ponto, nome simples nao pode ser FQDN
	if(!have_dot) return 3;

	// passou por todas as verificacoes de erros
	return 0;
}
// testar se string esta no formato ipv6
int is_ipv6(const char *str){
	struct in6_addr ipv6addr;
	if(!inet_pton(AF_INET6, str, &(ipv6addr))) return 1;
	return 0;
}
*/

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


// verificar se a string e' uma URL completa
// Precisa especificar o protocolo http, https ou ftp
int is_url(const char *input_url){
	int len = 0;
	int i = 0;
	int j = 0;
	int only_addr = 0;

	// posicao das partes
	int proto = 0;
	int posurladdr = 0;
	int is_ipv6addr = 0;

	// ponteiro das partes
	const char *point1 = NULL; // inicio do fqdn/endereco/ipv4/ipv6
	char *point2 = NULL;
	char *buffer = NULL;
	int buflen = 0;
	char numbers[10];

	// FQDN
	char *urladdr = NULL;
	int urladdr_len = 0;

	len = strlen(input_url);

	// tamanho minimo
	//                http://x/a.zip
	//                https://x/a.zip
	//                ftp://s/a.zip
	//
	if(len < 12) return 1;

	// Protocolo
	if( 0 == strncmp("http://", input_url, 7)) proto=7;
	if( 0 == strncmp("https://", input_url, 8)) proto=8;
	if( 0 == strncmp("ftp://", input_url, 6)) proto=6;
	if(!proto) return 2;
	point1 = (const char*) (input_url + proto);

	// printf("Pos-Proto[%d]: %s\n", proto, point1);

	buffer = (char *)malloc(len+2); if(!buffer) return 70;
	buflen = len - proto;
	memset(buffer, len+2, 1);
	memcpy(buffer, point1, buflen);
	// encontrar primeira ocorrencao nao a-z 0-9 . -
	if(buffer[0]=='[') is_ipv6addr = 1;
	for(i=0; i < buflen; i++){
		// se inicio em ipv6, devemos acabar no ']' ou com caracter nao-ipv6
		if(is_ipv6addr){
			// primeiro []
			if(buffer[i]=='[' && i == 0) continue;
			// divisao entre grupos
			if(buffer[i]==':') continue;
			// A-F
			if(buffer[i] >= 65 && buffer[i] <= 70) continue;
			// a-f
			if(buffer[i] >= 97 && buffer[i] <= 102) continue;
			// 0-9
			if(buffer[i] >= 48 && buffer[i] <= 57) continue;

			// acabou certo
			if(buffer[i]==']'){
				// incluir o ']' na contagem
				i++;
				// apartir do proto, pular os bytes processados ate aqui e 1 a mais para iniciar no proximo
				point2 = (char*)(buffer + i);

				// se um byte a frente for alem do limite, nao ultrapassar e anular ponteiro
				//if(proto + i > buflen) point2 = NULL;

				urladdr_len = i;
				break;
			}
			// acabou errado, precisava acabar no ]
			// printf("IPv6 ACABOU ERRADO: %c\n", buffer[i]);
			return 3;
		}

		// IPv4 ou FQDN

		// 0-9
		if(buffer[i] >= 48 && buffer[i] <= 57) continue;
		// A-Z
		if(buffer[i] >= 65 && buffer[i] <= 90) continue;
		// a-z
		if(buffer[i] >= 97 && buffer[i] <= 122) continue;
		// .
		if(buffer[i] == '.') continue;

		// Acabou em alguma coisa!
		point2 = (char*)(buffer + i);
		urladdr_len = i;
		break;

	}
	// caso haja somente FQDN
	if(!urladdr_len){
		urladdr_len = i;
		only_addr = 1;
		point2 = buffer;
	}

	urladdr = (char *)malloc(urladdr_len+1); if(!urladdr) return 72;
	memset(urladdr, urladdr_len+1, 1);
	memcpy(urladdr, buffer, urladdr_len);

	//printf("Buffer 1  [%d] (%d)...: %s\n", buflen, is_ipv6addr, buffer);
	//printf("FQDN      [%d]........: %s\n", urladdr_len, urladdr);
	//printf("Point 2A      ........: %s\n", point2);


	// ja temos o FQDN/IPv4/IPv6, analisar esse conteudo antes
	// de pular para o que vem depois
	if(is_ipv6addr){
		int ie = 0;
		// remover ultimo ']'
		urladdr[urladdr_len-1] = 0;
		urladdr[0] = 0;
		urladdr++;
		urladdr_len-=2;
		// se nao for ipv6, deu errado
		ie = is_ipv6(urladdr);
		if( ie ) return ie;
	}else{
		// ipv4 ou fqdn
		int is4 = 0;
		int isf = 0;
		is4 = is_ipv4(urladdr);
		isf = is_fqdn(urladdr);
		// printf("IPV4...........: %d [%s]\n", is4, urladdr);
		// printf("FQDN...........: %d [%s]\n", isf, urladdr);
		if( (is4+isf > 0) && ! IS_URL_XOR(is4, isf) ) return 7;
	}
	// Se for apenas FQDN, deu tudo certo
	if(only_addr) return 0;


	// Processar POS-FQDN
	// se for /, tudo depois pode ser repassado ao servidor
	if(!point2 || !point2[0] || point2[0] == '/') return 0;

	// Se nao tiver : entao o FQDN acabou com caracter invalido
	if(point2[0]!=':') return 9;


	// Analise de porta
	// - avancar apos o :
	point2++;
	if(!point2[0]) return 10; // acabou sem especificar a porta

	// Extrair numeros
	for(i=0; i < 10; i++) numbers[i] = 0;
	for(i=0; i < 10; i++){
		// acabou string pos-fqdn
		if(!point2[i]) break;
		// 0-9
		if(point2[i] >= 48 && point2[i] <= 57){
			numbers[j++] = point2[i];
			continue;
		}
		// '/' apos ler numeros
		if(point2[i]=='/' && j) break;
		// '/' sem ler numeros, porta nao especificada
		if(point2[i]=='/') return 11;

		// se acabou sem ser /, entao tem algo errado
		return 12;
	}
	// se o numero excedeu 5 caracteres, esta errado com certeza
	if(j > 5) return 13;

	// avaliar numero
	i = atoi(numbers);

	// se numero for zero ou maior que 65535
	if(i < 1 || i > 65535) return 14;

	// TUDO CERTO
	return 0;
}

//int main(const int argc, const char **argv){
int main_is_url(const char *progname, const int argc, const char **argv){
    if(argc<2) help_is_url();
	int r = is_url(argv[1]);
	return r;
}



















