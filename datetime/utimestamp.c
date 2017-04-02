
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>

void help_utimestamp(){
	printf("\n");
	printf("utimestamp\n");
	printf("Exibe o utimestamp\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: utimestamp\n");
	printf("\n");
	exit(1);
}

//int main(const int argc, const char **argv){
int main_utimestamp(const char *progname, const int argc, const char **argv){

	struct timespec tms;

	if (clock_gettime(CLOCK_REALTIME,&tms)){
		// exibir sem microtime
		printf("%d000007\n",(int)time(NULL));
		return 0;
	}

	// seconds, multiplied with 1 million
	int64_t micros = tms.tv_sec * 1000000;

	// Add full microseconds
	micros += tms.tv_nsec/1000;

	// round up if necessary
	if (tms.tv_nsec % 1000 >= 500) ++micros;

	printf("%"PRId64"\n",micros);

	return 0;

}
