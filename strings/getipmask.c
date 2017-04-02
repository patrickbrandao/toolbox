/*
	Recebe a mascara ipv4 decimal e retorna o numero de bits
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void help_getipmask(){
	printf("Use: getipmask (bits 0-32)\n");
	exit(1);
}

// principal
int main_getipmask(const char *progname, const int argc, const char **argv){

	int bits = 0;
	unsigned bytes[4];
	int m = 0, i = 0;

	// sem argumento
	if(argc < 2) help_getipbitmask();

	// coletar mascara
	m = atoi(argv[1]);

	// mascara precisa estar entre 0 e 32
	if(m < 0 || m > 32) return 2;

	// preencher bytes
	bytes[0] = bytes[1] = bytes[2] = bytes[3] = 0;
	i = 0;
	while(m > 0 && i < 4){
		if(m >= 8){ bytes[i++] = 255; m-=8; continue; }
		if(m == 7){ bytes[i++] = 254; m-=7; continue; }
		if(m == 6){ bytes[i++] = 252; m-=6; continue; }
		if(m == 5){ bytes[i++] = 248; m-=5; continue; }
		if(m == 4){ bytes[i++] = 240; m-=4; continue; }
		if(m == 3){ bytes[i++] = 224; m-=3; continue; }
		if(m == 2){ bytes[i++] = 192; m-=2; continue; }
		if(m == 1){ bytes[i++] = 128; m-=1; continue; }
	}

	// imprimir
	printf("%u.%u.%u.%u\n", bytes[0], bytes[1], bytes[2], bytes[3]);

    return 0;

}









