#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void help_is_numeric(){
	printf("\n");
	printf("is_numeric\n");
	printf("Verifica se os parametros estao no formato numerico (ou decimal),\n\tretorno stdno=0 em caso de correto ou >0 se estiver incorreto\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: is_numeric (data) [data] [data] [...]\n");
	printf("\n");
	exit(1);
}

int main_is_numeric(const char* progname, const int argc, const char **argv){

	int i = 0;
    if(argc<2) help_is_numeric();

	int r = is_numeric(argv[1]);
	return r;

}










