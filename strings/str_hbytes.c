
/*

	Representar quantidade de bytes em formato humano resumido

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include <inttypes.h>

void help_str_hbytes(){
	printf("\n");
	printf("str_hbytes\n");
	printf("Recebe um numero em bytes e retorna o formato abreviado\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: str_hbytes (number)\n");
	printf("\n");
	exit(1);
}

int main_str_hbytes(const char *progname, const int argc, const char **argv){
	uint64_t nbytes = 0;
	if(argc!=2) help_str_hbytes();

	nbytes = uint64_t_atoi(argv[1]);

	printf("%s\n", bytes_resume(nbytes));

	return 0;
}


