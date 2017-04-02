

void help_sumfilesize(){
	printf("\n");
	printf("sumfilesize\n");
	printf("Soma tamanho dos arquivo e retorna total em bytes\n");
	printf("\n");
	printf("Use: sumfilesize (file) [file] [file] [...]\n");
	printf("\n");
	exit(1);	
}

int main_sumfilesize(const char*progname, const int argc, const char **argv){
	int i;
	int g_total = 0;
    if(argc<2) help_sumfilesize();

    // processar arquivo ou lista de arquivos
	for(i=1;i<argc;i++){

		int size = 0;
		struct stat st;
		stat(argv[i], &st);
		size = st.st_size;
		g_total += size;

	}
	printf("%d\n", g_total);
}
