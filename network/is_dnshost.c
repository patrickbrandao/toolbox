#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void help_is_dnshost(){
	printf("\n");
	printf("is_dnshost\n");
	printf("Verifica se os parametros estao no formato de nome DNS (nome de host valido no DNS)\n");
	printf("Retorno stdno=0 em caso de correto ou >0 se estiver incorreto\n");
	printf("\n");
	printf("Exemplos reais esquisitos:\n");
	printf("\n");
	printf("\twww\n");
	printf("\tmailserver\n");
	printf("\twww-2\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: is_dnshost (word) [word] [word] [...]\n");
	printf("\n");
	exit(1);
}

int main_is_dnshost(const char *progname, const int argc, const char **argv){
    if(argc<2) help_is_dnshost();
	int r = is_dnshost(argv[1]);
	return r;
}



















