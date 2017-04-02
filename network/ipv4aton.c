#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include <sys/types.h>
#include <sys/param.h>
#include <arpa/inet.h>
#include <ctype.h>

/*
	
	Receber ip no primeiro parametro e retornar numero decimal de 32 bits
	
*/

void help_ipv4aton(){
	printf("\n");
	printf("ipv4aton\n");
	printf("Recebe um endereco IPv4, interpreta zeros a esquerda e omissoes e imprime na saida\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: ipv4aton (ipv4)\n");
	printf("\n");
	exit(1);	
}


int main_ipv4aton(const char *progname, const int argc, const char **argv){
    struct sockaddr_in sa;
    char str[INET_ADDRSTRLEN];

    if(argc!=2) help_ipv4aton();

	const char *ipv4str = (argv[1]);

	// ler ip em argv[1]
	sa.sin_addr.s_addr = inet_pton_ng(ipv4str);
	// inet_ntop(AF_INET, &(sa.sin_addr), str, INET_ADDRSTRLEN);
	printf("%d\n", sa.sin_addr.s_addr);

	return 0;
}











