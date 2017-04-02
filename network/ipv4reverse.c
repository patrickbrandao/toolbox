#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include <sys/types.h>
#include <sys/param.h>
#include <arpa/inet.h>
#include <ctype.h>

/*
	
	Receber ip no primeiro parametro e retornar notacao decimal perfeita, principalmente
	evitando interpretacao errada do zero a esquerda
	
	valores do usuario:
	
	192.168..1
	192.168.01.1
	192.168.001.01
	200...1
	
	500.1.2.3

*/

void help_ipv4reverse(){
	printf("\n");
	printf("ipv4reverse\n");
	printf("Recebe um endereco IPv4 e retorna sua notacao de nome reverso in-addr.arp\n");
	printf("\n");
	printf("Use: ipv4reverse (ipv4)\n");
	printf("\n");
	exit(1);	
}

int main_ipv4reverse(const char *progname, const int argc, const char **argv){
	int i;
    struct sockaddr_in sa;
    char str[INET_ADDRSTRLEN];
	const u_int8_t *ap;

    if(argc!=2) help_ipv4reverse();
    const char* ipv4str = argv[1];

	// ler ip da string
	sa.sin_addr.s_addr = inet_pton_ng(ipv4str);

	// ponteiro de 8 bits, gera array de 4 posicoes
	ap = (const u_int8_t *) &sa.sin_addr.s_addr;

	// imprimir byte a byte invertido
	printf("%d.%d.%d.%d.in-addr.arpa.\n", ap[3], ap[2], ap[1], ap[0]);

	return 0;
}


