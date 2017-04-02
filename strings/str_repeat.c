

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void help_str_repeat(){
	printf("Use: str_repeat (string) (num)\n");
	printf("     str_repeat -r (num) -s (string)\n");
	printf("     str_repeat -r (num) (string)\n");
	exit(1);
}

//int main(const int argc, const char **argv){
int main_str_repeat(const char *progname, const int argc, const char **argv){
	register int i = 0;
	int carg = 0, rarg = 0;
	char ch;
	int rcount = -1;
	char *string = NULL;
	int newline = 1;
	if(argc < 3) help_str_repeat();

	// Processar argumentos
	while ((ch = getopt(argc, (char * const*)argv, "nr:s:h?")) != EOF) {
		switch(ch) {
			// nao imprimir nova linha
			case 'n':
				newline = 0;
				carg++;
				break;

			// numero de repeticoes
			case 'r':
				rcount = atoi(optarg);
				if(rcount < 0) rcount = 0;
				carg+=2;
				break;

			// string
			case 's':
				string = strdup(optarg);
				carg+=2;
				break;

			case 'h':
			case '?':
			default:
				help_str_repeat();
		}
	}

	// deve sobrar uma string, a que sera repetida (-1 para remover o nome do programa)
	rarg = (argc - carg) -1;

	//- printf("[1] ARGC: %d CARG: %d RARG: %d STRING[%s] REPEAT[%d]\n", argc, carg, rarg, string, rcount);

	// sem mais argumentos
	if(rarg==0){
		// faltou a string
		if(string == NULL) help_str_repeat();
		// faltou especificar as repeticoes
		if(rcount < 0) help_str_repeat();
	}

	// processar argumentos que restam na sequencia string -> repeticoes
	// - STRING
	if(rarg > 0 && string == NULL){
		// string
		string = strdup(argv[carg+1]);
		carg++;
		rarg--;
	}
	// - REPETICOES
	if(rarg > 0 && rcount < 0){
		// repeticoes
		rcount = atoi(argv[carg+1]);
		carg++;
		rarg--;
	}

	//- printf("[2] ARGC: %d CARG: %d RARG: %d STRING[%s] REPEAT[%d]\n", argc, carg, rarg, string, rcount);

	// repetir
	for(i=0; i < rcount; i++) printf("%s", string);

	// nova linha no final?
	if(newline) printf("\n");

	return 0;
}





