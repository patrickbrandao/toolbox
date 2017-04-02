


void help_is_ipv4(){
	printf("\n");
	printf("is_ipv4\n");
	printf("Verifica o parametro informado esta no formato ipv4\n");
	printf("\n");
	printf("Use: is_ipv4 (ipv4)\n");
	printf("\n");
	exit(1);
}

int main_is_ipv4(const char *progname, const int argc, const char **argv){
	int i = 0;

    if(argc<2) help_is_ipv4();

	int r = is_ipv4(argv[1]);

	return r;

}


