
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>


void help_dater(){
	printf("Use: dater\n");
	printf("   Retorna a data/hora em formato americano corrido (yyyy-mm-dd-HHMMSS)\n");
	exit(1);
}

//int main(const int argc, const char **argv){
int main_dater(const char *progname, const int argc, const char **argv){
	time_t now = time(NULL);
	struct tm gmt = {0};
	int actyear = 0;

	localtime_r(&now, &gmt);
	actyear = 1900 + gmt.tm_year;

	// obter data-hora
	printf(
		"%04d-%02d-%02d-%02d%02d%02d\n",
		actyear, gmt.tm_mon+1, gmt.tm_mday,
		gmt.tm_hour, gmt.tm_min, gmt.tm_sec
	);
	return 0;
}

