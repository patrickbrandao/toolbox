
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>


void help_datebr(){
	printf("Use: datebr\n");
	printf("   Retorna a data em formato BR (dd/mm/yyyy)\n");
	exit(1);
}

//int main(const int argc, const char **argv){
int main_datebr(const char *progname, const int argc, const char **argv){
	time_t now = time(NULL);
	struct tm gmt = {0};
	int actyear = 0;

	localtime_r(&now, &gmt);
	actyear = 1900 + gmt.tm_year;

	// obter data-hora
	printf("%02d/%02d/%04d\n", gmt.tm_mday, gmt.tm_mon+1, actyear);
	return 0;
}

