/*

	Contar numero de nucleos

*/


#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>





void help_cpucount(){
	printf("Use:\n");
	printf("cpucount\n");
	printf("\tRetorna o numero de nucleos presentes no sistema (processadores)\n");
	exit(1);
}


int main_cpucount(const char* progname, const int argc, const char **argv){
	long nprocs = -1;
	long nprocs_max = -1;
	long max = 0;


	nprocs = sysconf(_SC_NPROCESSORS_ONLN);
	if (nprocs < 1){
		nprocs = 0;
	}

	nprocs_max = sysconf(_SC_NPROCESSORS_CONF);
	if (nprocs_max < 1){
		nprocs_max = 0;
	}
	if(nprocs > max) max = nprocs;
	if(nprocs_max > max) max = nprocs_max;
	if(max < 1) max = 1;

	printf ("%ld\n", max);
	exit (EXIT_SUCCESS);

}
