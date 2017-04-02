#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>


void help_ltrim(){
	printf("Use: ltrim (string)\n");
	printf("   Remove espacos a esquerda da string (antes)\n");
	exit(1);
}

//int main(const int argc, const char **argv){
int main_ltrim(const char *progname, const int argc, const char **argv){
	int i = 0;
	int j = 0;
	int len = 0;
	char *buffer = NULL;

	// se nao enviar nada, evitar mostrar help, apenas devolver vazio
	if(argc < 2) return 0;
	len = strlen(argv[1]);
	if(!len) return 0;

	// copiar
	buffer = (char *)malloc(len+2);
	if(!buffer) return 7;
	memset(buffer, 0, len+2);

	// gerar copia editavel
	strcpy(buffer, argv[1]);

	// Avancar buffer ate o primeiro byte nao-espaco
	while(*buffer == ' ') buffer++;

	// novo tamanho
	len = strlen(buffer);
	if(!len) return 0;

    printf("%s\n", buffer);

	// nenhum item encontrado
	return 0;
}












