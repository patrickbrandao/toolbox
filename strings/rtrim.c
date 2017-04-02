#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>


void help_rtrim(){
	printf("Use: rtrim (string)\n");
	printf("   Remove espacos a direita da string (depois)\n");
	exit(1);
}

//int main(const int argc, const char **argv){
int main_rtrim(const char *progname, const int argc, const char **argv){
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

	// percorrer de traz pra frente jogando zero em bytes espacos
	for(i = len - 1; i >= 0; i--){
		// printf("LEN=%d Traz pra frente: [%d] char=%c\n", len, i, buffer[i]);
		if(buffer[i]==' '){
			buffer[i] = 0;
			continue;
		}
		// nao-espaco detectado
		break;		
	}

    printf("%s\n", buffer);

	// nenhum item encontrado
	return 0;
}












