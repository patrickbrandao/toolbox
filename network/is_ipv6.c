

void help_is_ipv6(){
	printf("\n");
	printf("is_ipv6\n");
	printf("Verifica se o parametro informado e' ipv6\n");
	printf("\n");
	printf("Use: is_ipv6 (ipv6) [ipv6] [ipv6] [...]\n");
	printf("\n");
	exit(1);
}

int main_is_ipv6(const char* progname, const int argc, const char **argv){
	int i = 0;
    if(argc<2) help_is_ipv6();

	int r = is_ipv6(argv[1]);

	return r;

}







