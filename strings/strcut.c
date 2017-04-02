/*



	Cortar string em um unico comando (em vez de dois usando echo | cut)


*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>




void help_strcut(){
	printf("\n");
	printf("strcut\n");
	printf("Cortar string\n");
	printf("\n");
	printf("Use: strcut [opcoes] -s (string)\n");
	printf("\n");
	printf("Opcoes:\n");
	printf("  -c CHAR/STR        Caracter ou string divisora, padrao ':'\n");
	printf("  -n COLUMN          Numero da coluna, padrao 1\n");
	printf("  -s STRING          String a ser picada em pedacos\n");
	printf("  -x                 Corte exato. Nao imprimir ultima coluna como padrao.");
	printf("\n");
	exit(1);	
}


int main_strcut(const char *progname, const int argc, const char **argv){
//int main(const int argc, const char **argv){
	register int i = 0;          // contador generico
	register int fcount = 0;     // contador de campos percorridos
	char *p = NULL;              // ponteiro para parte da string

	// numero da coluna desejada
	int col = 1;

	// modo: 0=caracter divisor, 1=string divisora
	int mode = 0; 

	// corte exato?
	int cutexact = 0;

	// divisor
	char chrdiv = ':';
	char *strdiv = NULL;
	int strdivlen = 0;

	// string a ser trabalhada
	char *workstring = NULL;
	int wstrlen = 0;

	// precisamos de pelo menos 1 argumento (a string)
    if(argc < 2) help_strcut();

	// Processar argumentos
	char ch;
	while ((ch = getopt(argc, (char * const*)argv, "c:n:s:xh?")) != EOF) {
		switch(ch) {
			// string
			case 's':
				workstring = strdup(optarg);
				wstrlen = strlen(workstring);
				break;

			// numero da coluna
			case 'n':
				col = atoi(optarg);
				if(col < 1) col = 1;
				break;

			// caracter ou string delimitadora
			case 'c':
				strdivlen = strlen(optarg);
				switch(strdivlen){
					// sem divisor, ignorar
					case 0:
						continue;
						break;
					// divisor caracter
					case 1:
						chrdiv = optarg[0];
						mode = 0;
						break;

					// string
					default:
						strdiv = strdup(optarg);
						mode = 1;
						break;

				}
				break;

			// corte exato
			case 'x':
				cutexact = 1;
				break;

			case 'h':
			case '?':
			default:
				help_strcut();

		}
	}

	// criticas de sanidade
	// - sem string
	if(wstrlen < 1) exit(0);

	// Agora precisamos 'picar' a string
	fcount = 1;
	p = workstring;

	// procurar em modo dividor-caracter, mais rapido
	if(mode==0){
		// analisar byte a byte procurando divisor
		for(i=0; i < wstrlen; i++){
			char atch = workstring[i];

			// divisor?
			if(atch==chrdiv){
				// se ja estamos no campo desejado,
				// devemos finalizar a busca
				if(fcount==col){
					// achou!
					// caracter atual e' o fim
					workstring[i] = (char)(0);
					break;
				}else{
					// nada. Avancar a posicao da string de resultado
					// para depois do divisor
					p = workstring+i+1;
					fcount++;
				}
			}
		}
	}else{
	// procurar em modo divisor-string, mais complicado

		// procurar string divisora
		char *sp = p;
		while(sp && fcount <= col){

			// procurar string
			sp = strstr(p, strdiv);

			 // encontrou?
			 if(sp){
				// se ja estamos no campo desejado,
				// devemos finalizar a busca
			 	if(fcount==col){
			 		// temos que finalizar a string na posicao em que encontramos a divisao
			 		*sp = (char)(0);

			 		// a posicao de inicio da string permanece onde estava desde
			 		// a ultima vez em que nao encontramos (e avancamos para 1 byte alem do divisor)
			 		break;

				}else{
					// nada. Avancar a marcacao para a posicao onde o divisor encontrado termina
					p = sp+strdivlen;
					fcount++;
			 	}
			 }else{
			 	// nao encontrou, finalizar e econimizar uma coparacao no while()
			 	break;
			 } // if sp
		} // while
	} // if mode

	// usuario quer coluna exata mas essa coluna nao existe
	if(cutexact && fcount != col) return 0;

	// Exibir resultado
	printf("%s\n", p);


	return 0;

}



