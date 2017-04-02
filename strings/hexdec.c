/*

	Converter hexadecimal para decimal

*/

void help_hexdec(){
	printf("hexdec (hexadecimal)\n");
}

int main_hexdec(const char *progname, const int argc, const char **argv){
	int decimalNumber = 0;
	if(argc!=2) return 1;

	decimalNumber = (int)strtol((const char *)argv[1], NULL, 16);

	printf("%d\n",decimalNumber);

	return 0;

}
