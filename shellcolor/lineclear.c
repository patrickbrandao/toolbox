
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void help_lineclear(){
	printf("Use: lineclear [-w N] [-c C]\n");
	printf("Opcoes:\n");
	printf("    -w N       : numero de colunas a considerar (padrao automatico).\n");
	printf("    -c C       : caracter de limpeza (padrao espaco)\n");
	printf("    -n         : nao quebrar a linha apos limpa-la\n");
	printf("    -r         : posicionar na primeira linha (quando -n for informado)\n");
	exit( 1 );
}


int main_lineclear(const char *progname, const int argc, const char** argv){
//int main(const int argc, const char** argv){
	int i, colsize = 0, lines = 0, newline = 1, resetline = 0;
	char ch =  ' ';
	int opt;

	// processar argumentos
	while((opt = getopt((const int)argc, (char * const*)argv, "w:c:nrh")) != -1) {
		switch(opt) {

			// tamanho da linha manual
			case 'w':
				colsize = atoi(optarg);
				break;

			// caracter de limpeza
			case 'c':
				if(optarg && optarg[0]) ch = optarg[0];
				break;

			// nao quebrar a linha
			case 'n':
				newline = 0;
				break;

			// resetar posicao na linha
			case 'r':
				resetline = 1;
				break;

			case 'h':
				help_lineclear();
		} // switch
	} // while

	if(!colsize){
		struct winsize w;
		// obter dados da janela
		ioctl(0, TIOCGWINSZ, &w);

		// coletar dados
		if(!colsize) colsize = (int)w.ws_col;
		if(!lines) lines = (int)w.ws_row;
	}

	// padrao
	if(!colsize) colsize = 80;

	// espaco para quebra de linha
	//if(colsize>1) colsize--;

	/*
		printf("Colsize..: %d\n", colsize);
		printf("Lines....: %d\n", lines);
		printf("Char.....: [%c]\n", ch);
		printf("Newline..: %d\n", newline);
	*/

	// ir para o comeco
	printf("\r");

	// limpar linha
	for(i=0 ; i < colsize; i++) printf("%c", ch);

	// ir para proxima linha
	if(newline)
		printf("\n");
	//-

	// deixar cursor no inicio da linha?
	if(resetline)
		printf("\r");
	//-

	return 0;

}














