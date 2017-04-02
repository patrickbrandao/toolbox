
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void help_str_lower(){
	printf("Converter string para minusculas\n");
    printf("Use: str_lower (string)\n");
	exit(1);
}

//int main(const int argc, const char **argv){
int main_str_lower(const char *progname, const int argc, const char **argv){
	register int i = 0;
    int rcount = 1;
	char *string = NULL;
    if(argc!=2) help_str_lower();

    // string
    string = strdup(argv[1]);

    // converter para minusculas
    str_to_lower(string);

    // retornar na stdout
    printf("%s\n", string);
	return 0;
}



