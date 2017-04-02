
/*

	Inverte uma string

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help_str_reverse(){
	printf("\n");
	printf("str_reverse\n");
	printf("Recebe uma string e a devolve ao contrario\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: str_reverse (string)\n");
	printf("\n");
	exit(1);
}

int main_str_reverse(const char *progname, const int argc, const char **argv){
	char *strv;
	if(argc!=2) help_str_reverse();

	strv = strdup(argv[1]);
	str_reverse(strv);
	printf("%s\n", strv);

	return 0;
}


