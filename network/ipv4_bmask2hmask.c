
#include <stdio.h>

/*
	
	Recebe a mascara em bits (24) e retorna mascara decimal (255.255.255.0)

	Exemplo......: ipv4_bmask2hmask 8
		Retorno..: 255.0.0.0

	Exemplo......: ipv4_bmask2hmask 17
		Retorno..: 255.255.128.0

	Exemplo......: ipv4_bmask2hmask 32
		Retorno..: 255.255.255.252

*/
void help_ipv4_bmask2hmask(){
	printf("\n");
	printf("ipv4_bmask2hmask\n");
	printf("Recebe uma mascara de rede e retorna o numero de bits em 1\n");
	printf("\n");
	printf("Use: ipv4_bmask2hmask (mask)");
	printf("\n");
	printf("Exemplo: 'ipv4_bmask2hmask 16' retorna 255.255.0.0\n");
	printf("Exemplo: 'ipv4_bmask2hmask 24' retorna 255.255.255.0\n");
	printf("Exemplo: 'ipv4_bmask2hmask 32' retorna 255.255.255.255\n");
	printf("\n");
	exit(1);
}

int main_ipv4_bmask2hmask(const char *progname, const int argc, const char **argv){
//int main(const int argc, const char **argv){
	int bits = 0;

	// ajuda
	if (argc != 2) help_ipv4_bmask2hmask();

	bits = atoi(argv[1]);
	if(bits > 32) bits = 32;
	if(bits < 0) bits = 0;

	switch(bits){
		case 0: printf("0.0.0.0\n"); break;
		case 1: printf("128.0.0.0\n"); break;
		case 2: printf("192.0.0.0\n"); break;
		case 3: printf("224.0.0.0\n"); break;
		case 4: printf("240.0.0.0\n"); break;
		case 5: printf("248.0.0.0\n"); break;
		case 6: printf("252.0.0.0\n"); break;
		case 7: printf("254.0.0.0\n"); break;
		case 8: printf("255.0.0.0\n"); break;

		case 9: printf("255.128.0.0\n"); break;
		case 10: printf("255.192.0.0\n"); break;
		case 11: printf("255.224.0.0\n"); break;
		case 12: printf("255.240.0.0\n"); break;
		case 13: printf("255.248.0.0\n"); break;
		case 14: printf("255.252.0.0\n"); break;
		case 15: printf("255.254.0.0\n"); break;
		case 16: printf("255.255.0.0\n"); break;

		case 17: printf("255.255.128.0\n"); break;
		case 18: printf("255.255.192.0\n"); break;
		case 19: printf("255.255.224.0\n"); break;
		case 20: printf("255.255.240.0\n"); break;
		case 21: printf("255.255.248.0\n"); break;
		case 22: printf("255.255.252.0\n"); break;
		case 23: printf("255.255.254.0\n"); break;
		case 24: printf("255.255.255.0\n"); break;

		case 25: printf("255.255.255.128\n"); break;
		case 26: printf("255.255.255.192\n"); break;
		case 27: printf("255.255.255.224\n"); break;
		case 28: printf("255.255.255.240\n"); break;
		case 29: printf("255.255.255.248\n"); break;
		case 30: printf("255.255.255.252\n"); break;
		case 31: printf("255.255.255.254\n"); break;
		case 32: printf("255.255.255.255\n"); break;

	}

	return 0;
}











