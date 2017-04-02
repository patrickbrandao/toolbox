
void help_is_ipv4port(){
	printf("\n");
	printf("is_ipv4port\n");
	printf("Verifica se o parametro informao e um ip:porta\n");
	printf("\n");
	printf("Use: is_ipv4port (ipv4:port)\n");
	printf("\n");
	exit(1);
}

int main_is_ipv4port(const char *progname, const int argc, const char **argv){
	int i = 0;
    if(argc<2) help_is_ipv4port();

	int r = is_ipv4_port(argv[1]);
	return r;

}



















