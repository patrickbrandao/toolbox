

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void help_hex_decode(){
	printf("\n");
	printf("hex_decode\n");
	printf("Decodifica string em formato hexadecimal para formato normal");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: hex_decode (string)\n");
	printf("\n");
	exit(1);
}

int main_hex_decode(const char* progname, const int argc, const char **argv){
//int main(const int argc, const char **argv){
	unsigned char * _string;
	int _len = 0;
	if(argc != 2) help_hex_decode();

	_string = (unsigned char *)strdup(argv[1]);
	_len = strlen(_string);
	if(!_len) return 0;

	printf("%s\n", hex_decode(_string) );

	return 0;
}

















