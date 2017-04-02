
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void help_in_numrange(){
	printf("\n");
	printf("in_numrange\n");
	printf("Verifica se o numero esta dentro do range\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: in_numrange (num) (firstnum) (lastnum)\n");
	printf("\n");
	exit(1);
}

int main_in_numrange(const char* progname, const int argc, const char **argv){
	int i = 0;
	uint64_t num = 0, n_start = 0, n_last = 0;
	if(argc!=4) help_in_numrange();

	if(only_numbers(argv[1])) return 7;
	if(only_numbers(argv[2])) return 8;
	if(only_numbers(argv[3])) return 9;

	num = uint64_t_atoi(argv[1]);
	n_start = uint64_t_atoi(argv[2]);
	n_last = uint64_t_atoi(argv[3]);

	if(num < n_start) return 2;
	if(num > n_last) return 3;

	return 0;
}

