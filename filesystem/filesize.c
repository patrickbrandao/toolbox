




void help_filesize(){
	printf("\n");
	printf("filesize\n");
	printf("Informa tamanho do arquivo em bytes\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: filezie (file)\n");
	printf("\n");
	exit(1);	
}



int main_filesize(const char* progname, const int argc, const char **argv){
	int i;

    if(argc<2) help_filesize();

	for(i=1;i<argc;i++){
		int size = 0;
		struct stat st;

		stat(argv[i], &st);

		size = st.st_size;
		printf("%d\n", size);

	}
	return 0;

}
