
/*
	
	Receber 2 argumentos, o primeiro e' o caracter que deseja contar e o
	segundo argumento e posteriores
	e' o texto/frase

*/

void help_countchar(){
	printf("\n");
	printf("countchar\n");
	printf("Conta quantas vezes o byte (primeiro parametro) ocorre nos textos (parametros seguntes)\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: countchar (char) (text) [text] [...]\n");
	printf("\n");
	exit(1);	
}

int main_countchar(const char* progname, const int argc, const char **argv){
	int i;
	int count = 0;
	char byte = 0;

    if(argc<3) help_countchar();

    // byte
    byte = argv[1][0];

    // analisar 
	for(i=2;i<argc;i++){
		register int j;
		char *arg = strdup(argv[i]);
		while(*arg > 0){
			if(*arg==byte) count++;
			arg++;
		}
	}

	printf("%d\n", count);

	if(!count) return 1;
	return 0;

}

