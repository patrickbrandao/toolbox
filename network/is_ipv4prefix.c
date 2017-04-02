


void help_is_ipv4prefix(){
	printf("\n");
	printf("is_ipv4prefix\n");
	printf("Verifica se o parametro informado e' um prefixo ipv4/bits\n");
	printf("\n");
	printf("Use: is_ipv4prefix (ipv4/prefix)\n");
	printf("\n");
	exit(1);
}

int main_is_ipv4prefix(const char *progname, const int argc, const char **argv){
	int i = 0;
    if(argc<2) help_is_ipv4prefix();
	int r = is_ipv4_prefix(argv[1]);
	return r;
}



















