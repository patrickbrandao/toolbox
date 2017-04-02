
/*

	Detecta linhas duplicadas

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <getopt.h>


static void help_fstrdup(){
	printf("Use: fstrdup (file)\n");
	exit(1);
}

int main_fstrdup(const char *progname, const int argc, const char** argv){

	FILE *FDESC = NULL;
	char *file = NULL;

	// linha atual
	char *line = NULL;

	// linha anterior
	char *lastline = NULL;

	 ssize_t readbytes = 0;
	 size_t readlen = 1000;

	 // contador de duplicacoes
	 size_t dupcount = 0;

	// arquivo deve ser o argumento
	if(argc != 2) help_fstrdup();

	file = strdup(argv[1]);

	 // testar acesso ao arquivo
	if(access(file, R_OK)!=0){
		fprintf(stderr, "Incapaz de acessar arquivo '%s'\n", file);
		return 2;
	}

	// abrir arquivo
   FDESC = fopen(file, "r");
	if (FDESC == NULL){
		fprintf(stderr, "Incapaz de abrir arquivo '%s'\n", file);
		return 3;
	}

	while ((readbytes = getline(&line, &readlen, FDESC)) != -1) {
		char *found;
		int id;
		int idfound = 0;
		char *p = line;

		// probelma ao alocar linha
		if(!p) continue;

		// linha em branco podem duplicar
		// queremos apenas conteudo duplicado
		if(p[0] == '\0' || p[0] == '\n') continue;

		// retirar quebra de linha
		while(p){
			if(*p=='\n'){
				*p = '\0';
				break;
			}
			p++;
		}

		// primeira linha
		if(lastline){
			// segunda linha em diante
			if(strcmp(line, lastline)==0){
				// linha duplicada
				dupcount++;
				// imprimir linha duplicada
				printf("%s\n", line);
			}
		}

		// gerar copia da linha atual
		if(lastline) free(lastline);
		lastline = strdup(line);

	}
	// fechar arquivo
	fclose(FDESC);

	// retornar stdno 7 quando houver duplicacoes
	if(dupcount) return 7;

	return 0;
}





