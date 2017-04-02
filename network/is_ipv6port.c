#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>

void help_is_ipv6port(){
	printf("\n");
	printf("is_ipv6port\n");
	printf("Verifica se o parametro de entrada e' ipv6 com porta\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: is_ipv6port ([ipv6]:port)\n");
	printf("\n");
	exit(1);
}

int main_is_ipv6port(const char *progname, const int argc, const char **argv){
	int i = 0;

    if(argc<2) help_is_ipv6port();
	int r = is_ipv6_port(argv[1]);

	return r;

}



















