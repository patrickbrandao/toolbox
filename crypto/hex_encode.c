

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void help_hex_encode(){
	printf("\n");
	printf("hex_encode\n");
	printf("Codifica string em formato hexadecimal (2 caracteres na saida para cada 1 byte na entrada)");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: hex_encode (string)\n");
	printf("\n");
	exit(1);
}

int main_hex_encode(const char* progname, const int argc, const char **argv){
//int main(const int argc, const char **argv){
	unsigned char * _string;
	int _len = 0;
	if(argc != 2) help_hex_encode();

	_string = (unsigned char *)strdup(argv[1]);
	_len = strlen(_string);
	if(!_len) return 0;

	printf("%s\n", hex_encode(_string, &_len) );

	return 0;
}

















