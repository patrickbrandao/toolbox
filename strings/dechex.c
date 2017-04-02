/*

	Converter decimal para hexadecimal

*/

void help_dechex(){
	printf("dechex (decimal)\n");
}

int main_dechex(const char *progname, const int argc, const char **argv){
	long int decimalNumber = 0;
	if(argc!=2) return 1;

	decimalNumber = atoi(argv[1]);
	printf("%X\n",decimalNumber);

	return 0;

}

