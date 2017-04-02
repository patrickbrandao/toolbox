
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <ctype.h>

void help_str_cmpi(){
	printf("Use: str_cmpi (string1) (string2)\n");
    printf("Verifica se a string1 e' igual a string2 sem case-insensitive: sim (stdno=0) ou nao (stdno=1)\n");
	exit(1);
}


//int main(const int argc, const char **argv){
int main_str_cmpi(const char *progname, const int argc, const char **argv){
    char *string1;
    char *string2;
    if(argc!=3) help_str_cmpi();

    string1 = strdup(argv[2]);
    string2 = strdup(argv[1]);

    str_to_lower(string1);
    str_to_lower(string2);

    if(strcmp(string1, string2)==0) return 0;
    return 1;
}



