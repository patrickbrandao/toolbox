

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void help_timestamp(){
	printf("\n");
	printf("timestamp\n");
	printf("Exibe o timestamp\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: timestamp\n");
	printf("\n");
	exit(1);
}

//int main(const int argc, const char **argv){
int main_timestamp(const char *progname, const int argc, const char **argv){
	printf("%d\n",(int)time(NULL));
	return 0;
}

