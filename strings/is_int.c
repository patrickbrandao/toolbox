



void help_is_int(){
	printf("\n");
	printf("is_int\n");
	printf("Verifica se os parametros estao no formato numerico inteiro,\n\tretorno stdno=0 em caso de correto ou >0 se estiver incorreto\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: is_int (data) [data] [data] [...]\n");
	printf("\n");
	exit(1);
}




int main_is_int(const char *progname, const int argc, const char **argv){
	int i = 0;
    if(argc<2) help_is_int();

	int r = is_integer(argv[1]);

	return r;

}




