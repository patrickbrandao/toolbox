#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void help_is_fqdn(){
	printf("\n");
	printf("is_fqdn\n");
	printf("Verifica se os parametros estao no formato FQDN (nome de host valido no DNS)\n");
	printf("Retorno stdno=0 em caso de correto ou >0 se estiver incorreto\n");
	printf("\n");
	printf("Exemplos reais esquisitos:\n");
	printf("\n");
	printf("\t3.141592653589793238462643383279502884197169399375105820974944592.com\n");
	printf("\twww.thelongestlistofthelongeststuffatthelongestdomainnameatlonglast.com\n");
	printf("\twww.openoffshorebankaccountsfornonresidents.com\n");
	printf("\twww.llanfairpwllgwyngyllgogerychwyrndrobwllllantysiliogogogoch.co.uk\n");
	printf("\twww.abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijk.com\n");
	printf("\n");
	printf("Exemplos comuns:\n");
	printf("\tintranet.br\n");
	printf("\twww.google.com.br\n");
	printf("\tintranet.acme.yyy\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: is_fqdn (fqdn) [fqdn] [fqdn] [...]\n");
	printf("\n");
	exit(1);
}

int main_is_fqdn(const char *progname, const int argc, const char **argv){
    if(argc<2) help_is_fqdn();
	int r = is_fqdn(argv[1]);
	return r;
}



















