
void help_strlike(){
	printf("\n");
	printf("strlike\n");
	printf("Testa a semelhanca entre duas strings (parametro 1 e parametro 2)\n");
	printf("Primeiro parametro deve ser a palavra completa, segunda parametro o versao reduzida\n");
	printf("Retorna o numero de bytes semelhantes\n");
	printf("\n");
	printf("Use: strlike (string1) (string2)\n");
	printf("\n");
	exit(1);	
}


int main_strlike(const char *progname, const int argc, const char **argv){
	int i = 0;
    if(argc!=3) help_strlike();

    i = strmathcount(argv[1], argv[2], 0);
    printf("%d\n", i);

    // stdno 0 apenas se encontrou
    return i ? 0 : 1;

}




