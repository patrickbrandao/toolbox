

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void help_in_wordlist(){
	printf("\n");
	printf("in_wordlist\n");
	printf("Verifica se a primeira palavra consta numa frase. Caracters ignorados: ,;|/ espaco\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: in_wordlist (word) (string)\n");
	printf("\n");
	exit(1);
}

#define WORD_END(chr)	(chr==',' || chr==';' || chr=='|' || chr=='/' || chr==' ' || chr=='\n' || chr=='\r' || chr=='\t')

//int main(const int argc, const char **argv){
int main_in_wordlist(const char *progname, const int argc, const char **argv){
	int i = 0;
	int word_len = 0;
	int context_len = 0;
    if(argc!=3) help_in_wordlist();

    // palavra
    char *word = strdup(argv[1]);
    word_len = strlen(word);
    if(!word_len) return 1;

    // texto
    char *context = strdup(argv[2]);
    context_len = strlen(context);
    if(!context_len) return 2;

    // impossivel
    if(word_len > context_len) return 3;

    // 1 a 1
    // printf("word_len=%d context_len=%d\n", word_len, context_len);
    if(word_len == context_len) if(strcmp(word, context)==0) return 0; else return 4;


    // Parte dificil.
    // Interpretar palavra por palavra e comparar
	char *wbuffer = malloc(word_len+2); bzero(wbuffer, word_len+1);
	int wbuffer_len = 0;
	int inskip = 0;
	// cuidado com o zero
	for(i=0; i <= context_len; i++){
		char ch = context[i];

		// caracter do contexto
		if( ! WORD_END(ch) ) wbuffer[wbuffer_len++] = ch;

		if( WORD_END(ch) || ch == '\0' ){
			// printf("--> Palavra terminada: [%s] wbuffer_len=[%d] word_len=[%d]\n", wbuffer, wbuffer_len, word_len);

			// se encontramos um divisor
			// - verificar se ja deu pra comparar
			if(strcmp(word, wbuffer)==0){
				// printf(" 1 -> Achou word[%s] wbuffer[%s]", word, wbuffer);
				return 0;
			}
			//temos que zerar a palavra em buffer
			if(wbuffer_len){
				bzero(wbuffer, word_len+1);
				wbuffer_len = 0;
			}
			inskip = 0;
			continue;
		}


		// printf("word[%s] CH=[%c] inskip=[%d] word_len=[%d] wbuffer_len=[%d] wbuffer=[%s]\n", word, ch, inskip, word_len, wbuffer_len, wbuffer);

		/*
		if(wbuffer_len==word_len && (i < context_len && WORD_END(context[i+1]) ) && strcmp(word, wbuffer)==0){
			printf(" 2 -> Achou word[%s] wbuffer[%s]", word, wbuffer);
			return 0;
		}
		*/
		// alcancamos o tamanho da palavra
		//if(wbuffer_len==word_len){
		//	printf(" 2 -> Achou word[%s] wbuffer[%s]", word, wbuffer);
		//	return 0;
		//}




	}



	return 9;

}




