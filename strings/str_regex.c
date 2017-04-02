
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void help_str_regex(){
	printf("Use: str_regex (string) (regex)\n");
    printf("Verifica se a string atende a regex (stdno=0) ou nao (stdno=1)\n");
	exit(1);
}

//int main(const int argc, const char **argv){
int main_str_regex(const char *progname, const int argc, const char **argv){
    int ret = 0;
    char *regex;
    char *string;
    if(argc!=3) help_str_regex();

    regex = strdup(argv[2]);
    string = strdup(argv[1]);

    ret = test_regex( (const char *)(regex), (const char *)(string));

    return ret;
}






