
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void help_strlen(){
	printf("Use: strlen (string)\n");
	exit(1);
}

int main_strlen(const char *progname, const int argc, const char **argv){
	register int i = 0;
    int len = 0;
	char *string = NULL;
    if(argc!=2) help_strlen();

    // string
    string = strdup(argv[1]);

    len = strlen(string);
    printf("%i\n", len);

	// nenhum item encontrado
	return 0;
}



















