
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>
#include <ctype.h>


void help_mac_read(){
	printf("\n");
	printf("mac_read\n");
	printf("Ler MAC-ADDRESS em qualquer formato e retornar em formato Linux\n");
	printf("Retorna formato: XX:XX:XX:XX:XX:XX\n");
	printf("Caso o formato esteja sintaticamente incorreto, retorna vazio e STDNO 7\n");
	printf("\n");
	printf("Use: mac_read (mac-address)\n");
	printf("\n");
	exit(1);
}

// Tamanho minimo possivel: 001122aabbcc = 12
// Tamanho maximo possivel: 0.0.1.1.2.2.a.a.b.b.c.c = 23
int main_mac_read(const char *progname, const int argc, const char **argv){
//int main(const int argc, const char **argv){
	if(argc!=2) help_mac_read();
	int i = 0;
	int idx = 0, len;
	char macaddr[12];
	const char *str = argv[1];

	// tamanho da entrada
	len = strlen(argv[1]);

	// menor que o minimo possivel
	if(len < 12) return 5;
	// maior que o maximo possivel
	if(len > 23) return 6;

	// ler bytes hexadecimais
	for(i=0; i < 12; i++) macaddr[i] = 0;

	for(i=0; i < len; i++){
		char chr = str[i];

		if(isxdigit(chr)){
			// estourour?
			if(idx > 11) return 8;

			// coletar
			macaddr[idx++] = chr;
			continue;
		}
	}

	// nao coletou a quantidade necessaria
	if(idx!=12) return 7;

	// imprimir resultado
	printf("%c%c:%c%c:%c%c:%c%c:%c%c:%c%c\n", 
		macaddr[0], macaddr[1],
		macaddr[2], macaddr[3],
		macaddr[4], macaddr[5],
		macaddr[6], macaddr[7],
		macaddr[8], macaddr[9],
		macaddr[10], macaddr[11]
	);

	// ok
	return 0;
}













