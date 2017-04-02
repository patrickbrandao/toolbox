
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void help_in_str(){
	printf("Use: in_str (word) (string)\n");
	exit(1);
}

int main_in_str(const char *progname, const int argc, const char **argv){
	register int i = 0;
	char *word = NULL;
	char *string = NULL;
	char *res;
    if(argc!=3) help_in_str();

    // palavra
    word = strdup(argv[1]);

    // frase
    string = strdup(argv[2]);

    // verificar se esta contido
    str_to_lower(word);
    str_to_lower(string);

    // procurar
    res = strstr(string, word);

    if(res==NULL) return 1;

	// nenhum item encontrado
	return 0;
}



















