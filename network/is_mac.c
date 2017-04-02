


void help_is_mac(){
	printf("\n");
	printf("is_mac\n");
	printf("Verifica se o parametro esta num formato mac reconhecido\n");
	printf("Formatos aceitos: 00:11:22:33:44:55, 00-11-22-33-44-55, 001122334455, 001122-334455\n");
	printf("\n");
	printf("Use: is_mac (mac-address)\n");
	printf("\n");
	exit(1);
}


int main_is_mac(const char *progname, const int argc, const char **argv){
	int i = 0;
    if(argc!=2) help_is_mac();

	int r = is_mac(argv[1]);

	return r;

}



















