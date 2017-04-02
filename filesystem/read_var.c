
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>


void help_read_var(){
	printf("\n");
	printf("read_var\n");
	printf("Obter valor de variavel em arquivo onde cada linha possui um par VAR=VALUE\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: read_var (file) (varname)\n");
	printf("Erros retornados via STDNO:\n");
	printf("\t 1 = ajuda necessaria\n");
	printf("\t 2 = numero de argumentos incorretos\n");
	printf("\t 3 = nome do arquivo vazio\n");
	printf("\t 4 = nome da variavel vazia\n");
	printf("\t 5 = impossivel ler arquivo (access R_OK != 0)\n");
	printf("\t 6 = erro ao abrir arquivo\n");
	printf("\t 7 = variavel nao encontrada\n");
	printf("\n");
	exit(1);	
}


int main_read_var(const char* progname, const int argc, const char **argv){
//int main(const int argc, const char **argv){
	int i;
	char *file = NULL;
	char *line = NULL;
	char *buffer[1024];
	char *neededvarname = NULL;
	
	FILE *CONFD = NULL;
	ssize_t readbytes = 0;
	size_t readlen = 1000;

	bzero(buffer, sizeof buffer);

	// precisar informar nome do arquivo e variavel
	if(argc!=3) return 2;

	// Arquivo de configuracao
	file = strdup(argv[1]);
	neededvarname = strdup(argv[2]);
	i = strlen(file); if(i < 2) return 3;
	i = strlen(neededvarname); if(i < 2) return 4;

	 // testar acesso ao arquivo
	if(access(file, R_OK)!=0){ return 5; }

	// abrir arquivo
	CONFD = fopen(file, "r");
	if (CONFD == NULL){ return 6; }

	// printf("PROCURAR POR VARIAVEL [%s]\n", neededvarname);

	while ((readbytes = getline(&line, &readlen, CONFD)) != -1) {
		char *div;
		char *ediv;
		int i = 0;
		int j = 0;
		int varnamelen = 0;
		int valuelen = 0;
		char varname[32]; bzero(varname, sizeof varname);
		char varvalue[32]; bzero(varvalue, sizeof varvalue);
		char *varpt = NULL;
		char *varvl = NULL;
		int stage = 0;

		// comentario obvio
		if(line[0]=='#') continue;

		// precisa ter divisor de variavel=valor
		ediv = strchr(line, '=');
		if(ediv == NULL) continue;

		// o nome da variavel deve estar contida na linha
		div = strstr(line, neededvarname);
		if(div==NULL) continue;

		// printf("PRE-LINE: [%s]\n", line);

		// obter nome da variavel
		for(i = 0; i < readlen && varnamelen < 32; i++){
			// ignorar espacos e tabs no inicio
			if(!varnamelen && (line[i]==' ' || line[i]=='\t') ) continue;

			// interromper leitura quando a palavra acabar
			if(varnamelen && ! (isalnum(line[i]) || line[i] == '_' )) break;

			// sinal de igual, parar
			if(line[i] == '=') break;

			// copiar byte para o nome da variavel
			varname[varnamelen++] = line[i];
		}

		// se o nome obtido nao for igual o nome procurado, ignorar
		if(strcmp(varname, neededvarname) != 0) continue;

		// pegar valor, avancar 1 caracter para pular o '='
		ediv++;
		valuelen = strlen(ediv);

		// fazer trim no valor
		if(valuelen){
			// retirar espacos do final
			for(i = valuelen -1; i >= 0; i--){
				if(isspace(ediv[i])){
					ediv[i] = 0;
					valuelen--;
					continue;
				}
				break;
			}
			// retirar espacos do comeco
			for(i = 0; i < valuelen; i++){
				if(isspace(ediv[i])){
					ediv++;
					continue;
				}
				break;
			}
		}
		// encontrou, encerrar

		printf("%s\n", ediv);
		fclose(CONFD);
		return 0;
	}
	fclose(CONFD);

	return 7;
}






