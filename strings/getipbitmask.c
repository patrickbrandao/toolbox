/*
	Recebe a mascara ipv4 decimal e retorna o numero de bits
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void help_getipbitmask(){
	printf("Use: getipbitmask (mask x.x.x.x)\n");
	exit(1);
}

// principal
int main_getipbitmask(const char *progname, const int argc, const char **argv){
	char *mask;
	unsigned int bitmask = 24;
	unsigned bytes[4];
	int i;

	// sem argumento
	if(argc < 2) help_getipbitmask();

	// coletar mascara
	mask = strdup(argv[1]);

	// mascara vazia
	if(mask==NULL){
		printf("%u\n", bitmask);
		return 2;
	}

	// ler os 4 bytes, vamos aproximar do verdadeiro para evitar
	// erros de digitacao do usuario, exempl: 255.255.255.129
	bytes[0] = bytes[1] = bytes[2] = bytes[3] = 0;
	if ( sscanf(mask, "%u.%u.%u.%u", &bytes[0], &bytes[1], &bytes[2], &bytes[3]) == 4 ){

		// 4 bytes lidos
		unsigned int x = 0;
		unsigned int lock = 0;
		for(i=0;i<4;i++){
			int b = bytes[i];
			if(b>=255){ x+=8; continue; }
			if(lock) break;
			if(b>=254-1){ x+=7; lock=1; continue; }
			if(b>=252-2){ x+=6; lock=1; continue; }
			if(b>=248-4){ x+=5; lock=1; continue; }
			if(b>=240-8){ x+=4; lock=1; continue; }
			if(b>=224-8){ x+=3; lock=1; continue; }
			if(b>=192-16){ x+=2; lock=1; continue; }
			if(b>=128-32){ x+=1; lock=1; continue; }
		}
		bitmask = x;
	}else{
		// erro de leitura da string
		printf("%u\n", bitmask);
		return 3;
	}

	printf("%d\n", bitmask);

    return 0;

}









