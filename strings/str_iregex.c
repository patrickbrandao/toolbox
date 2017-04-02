
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <ctype.h>

void help_str_iregex(){
	printf("Use: str_iregex (string) (regex)\n");
    printf("Verifica se a string atende a regex sem case-sensitive (stdno=0) ou nao (stdno=1)\n");
	exit(1);
}


//int main(const int argc, const char **argv){
int main_str_iregex(const char *progname, const int argc, const char **argv){
    int ret = 0;
    char *iregex;
    char *string;
    if(argc!=3) help_str_iregex();

    iregex = strdup(argv[2]);
    string = strdup(argv[1]);

    str_to_lower(string);
    str_to_lower(iregex);

    ret = test_regex( (const char *)(iregex), (const char *)(string));

    return ret;
}



