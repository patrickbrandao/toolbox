/*

	Recebe um numero de bytes com ou sem abreviacao e retorna o numero de bytes corretos

	BUGADO
	BUGADO
	BUGADO
	BUGADO
	BUGADO
	BUGADO
	BUGADO
	BUGADO
	BUGADO
	BUGADO
	BUGADO
	BUGADO
	BUGADO
	BUGADO
	BUGADO
	BUGADO

	Falta suportar leitura de mega

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void help_get_bytes(){
	printf("\n");
	printf("get_bytes\n");
	printf("    Use: get_bytes [opt] (sting)\n");
	printf("\n");
	printf("Retorna numero de bytes da string interpretada.\n");
	printf(" Parametros:\n");
	printf("    -k  : retorna em numero de kbytes\n");
	printf("    -m  : retorna em numero de megabytes\n");
	printf("    -g  : retorna em numero de gigabytes\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	exit(1);
}

void _print_bytes(int _xbytes, int _xformat){
    // debug
    printf("\n");
    printf("Bytes.........: %d\n", _xbytes);
    printf("OutFormat.....: %d\n", _xformat);

	printf("OUTPUT BYTES...: [%d]\n", _xbytes);

	exit(0);
}

int main(const int argc, const char **argv){
//- int main_get_bytes(const char *progname, const int argc, const char **argv){
	char *input_string = NULL;
	int i = 0, input_len = 0;

	// grandeza de retorno:
	// 0 = bytes
	// 1 = kbytes
	// 2 = megabytes
	// 3 = gigabytes
	// 4 = terabytes
	int _outformat = 0;
	long double _bytes = 0;

	// separar numeros de letras
	int _in_numbers = 1; // flag para interromper leitura de numeros quando encontrar alfanum
	int _start_read = 0; // ignorar espacos no inicio
	char _numbers[32]; int _numcount = 0;

	// limpar salao
	for(i=0; i < 32; i++){ _numbers[i] = 0; }

    if(argc<2) help_get_bytes();

	// processar argumentos
	for(i=1; i < argc; i++){

		// verificar se e' opcao
		// - ajuda
		if(0 == strcmp("-h", argv[i])) help_get_bytes();
		if(0 == strcmp("--help", argv[i])) help_get_bytes();

		// - formatos
		if(0 == strcmp("-k", argv[i])){ _outformat = 1; continue; }
		if(0 == strcmp("-m", argv[i])){ _outformat = 2; continue; }
		if(0 == strcmp("-g", argv[i])){ _outformat = 3; continue; }

		// - string
		input_string = strdup(argv[i]);
	}

    // Analisar string
    if(input_string && input_string[0]) input_len = strlen(input_string);
    if(!input_len) _print_bytes(_bytes, _outformat);


    // Separar numeros de caracteres
    // iniciar filtragem
    for(i=0; i < input_len; i++){

    	// nao esturar buffers
    	if(i >= 30) break;

    	char ch = input_string[i];

		// letras minusculas
		if( (ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90) ){
			_in_numbers = 0; // encerrar leitura de numeros
			ch = tolower(ch);
			if(ch=='b'){ _outformat = 0; break; }
			if(ch=='k'){ _outformat = 1; break; }
			if(ch=='m'){ _outformat = 2; break; }
			if(ch=='g'){ _outformat = 3; break; }
			continue;
		}

		// numeros
		if(ch >= 48 && ch <= 57){
			if(_in_numbers){
				// catalogar
				_numbers[_numcount++] = ch;
			}
			continue;
		}

	}

	// converter para numeros
	_bytes = (long double) atoi(_numbers);
	printf("_numbers.....: [%s]\n", _numbers);
	printf("_bytes.......: [%d]\n", _bytes);
	printf("_outformat...: [%d]\n", _outformat);

	// elevar para grandeza lida
	switch(_outformat){
		case 1: _bytes = _bytes * 1024; break;
		case 2: _bytes = _bytes * (1024 * 1024); break;
		case 3: _bytes = _bytes * (1024 * 1024 * 1024); break;
	}

	_print_bytes(_bytes, _outformat);

	return 0;
}























