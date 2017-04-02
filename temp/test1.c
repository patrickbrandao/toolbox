


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdlib.h>
//#include "../toolbox.h"


#define MY_MALLOC(PTR, MEMSIZE)		PTR = malloc(MEMSIZE+1); if(PTR){ bzero(PTR, MEMSIZE+1); }else exit(1);
#define MY_STRDUP(PTR, STR)			MY_MALLOC(PTR, strlen(STR) * sizeof(char) + 1); strcpy(PTR, STR)
#define STR_EXIST_OR_RETURN(STR)	if(!STR || !STR[0]) return


// inverter uma string
void str_reverse(char *str){
	char *buf = NULL;
	register int len, i;
	register int total;

	// nada a fazer
	STR_EXIST_OR_RETURN(str);

	// tamanho da string
	len = strlen(str);

	// nao da pra inverter 1 byte ne!
	if(len <= 2) return;

	// alocar
	total = (len+1) * (sizeof(char)) + 1;
	MY_MALLOC(buf, total);

	// inverter
	for(i=0; i < len; i++) buf[i] = str[len-i-1];

	// copiar de volta pro original
	for(i=0; i < len; i++) str[i] = buf[i];
}


// retirar todos os caracteres nao-numericos
void str_only_numbers(char *str){
	register int len = 0, k = 0, i = 0;
	// nada a fazer
	STR_EXIST_OR_RETURN(str);
	len = strlen(str);
	for(i = 0; i < len; i++){
		if(isdigit(str[i]))
			str[k++] = str[i];
		//-
	}
	// apagar o resto
	for(i = k; i < len; i++) str[i] = 0;
}


// formatar numero, entrada: 1234 saida 1.234
char *str_number_format(const char *input){
	register int alocsize = 0, inputlen = 0;
	register int newlen = 0, k, m, n;
	char *ret = NULL, *workspace = NULL;

	// nada a fazer
	STR_EXIST_OR_RETURN(input) ret;
	//if(!input || !input[0]) return ret;

	// tamanho da entrada
	inputlen = strlen(input);
	if(inputlen < 4){
		// nada a fazer, duplicar e retornar
		MY_STRDUP(ret, input);
		return ret;
	}

	// tamanho da string para trabalho
	alocsize = (inputlen * sizeof(char)) + (inputlen > 3 ? inputlen / 3 : inputlen) + 3;

	// alocar espaco para retorno e gerar copia local
	MY_MALLOC(ret, alocsize);
	MY_MALLOC(workspace, alocsize);
	strcpy(ret, input);

	// apenas numeros sao permitidos
	str_only_numbers(ret);

	newlen = strlen(ret);
	if(!newlen++) sprintf(ret, "0");

	// inverter ordem
	str_reverse(ret);

	// temos apenas os numeros invertidos, escreve-los com pontos
	k = 0;
	n = 1;
	for(m = 0; m < newlen; m++){
		workspace[k++] = ret[m];
		if(n++ == 3){ n = 1; if( m+2 < newlen) workspace[k++] = '.'; }
	}
	// inverter novamente
	str_reverse(workspace);
	return workspace;
}

#define ARRDIM(x) (sizeof(x)/sizeof(*(x)))
static const char     *bytes_resume_sizes[]   = { "EiB", "PiB", "TiB", "GiB", "MiB", "KiB", "B" };
static const uint64_t  bytes_resume_exbibytes = 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL;
char *bytes_resume(uint64_t size){
	char     *result = (char *) malloc(sizeof(char) * 20);
	uint64_t  multiplier = bytes_resume_exbibytes;
	int i;
	for (i = 0; i < ARRDIM(bytes_resume_sizes); i++, multiplier /= 1024){   
		if (size < multiplier) continue;
		if (size % multiplier == 0)
			sprintf(result, "%" PRIu64 " %s", size / multiplier, bytes_resume_sizes[i]);
		else
			sprintf(result, "%.1f %s", (float) size / multiplier, bytes_resume_sizes[i]);
		//-
		return result;
	}
	strcpy(result, "0");
	return result;
}

// ler string para uint64_t
uint64_t uint64_t_atoi(const char *strnumber){
	uint64_t ret = 0, gmult = 1;

	int len = 0, i;
	STR_EXIST_OR_RETURN(strnumber) ret;

	len = strlen(strnumber);
	if(!len) return ret;

	for(i=0; i < len; i++){
		// obter caracter
		char ch = strnumber[i];
		uint64_t tempn = 0;

		// ignorar nao-numerico
		if(ch < 48 || ch > 57) continue;
		tempn = (uint64_t)(ch - 48);
		ret += (gmult * tempn);
		gmult *= 10;
	}
	return ret;
}


int main(int argc, char** argv){
	uint64_t n0 = 0;

	n0 = uint64_t_atoi(argv[1]);

	printf("n0....: %s\n", bytes_resume(n0));
/*
	char *str1 = "1";
	char *str2 = "12";
	char *str3 = "123";
	char *str4 = "1234";
	char *str5 = "12345";
	char *str6 = "123456";
	char *str7 = "1234567";
	char *str8 = "12345678";
	char *str9 = "123456789";
	char *stra = "1234567890";
	char *strb = "12345678901";
	char *strc = "123456789012";
	char *strd = "1234567890123";

	uint64_t n1 = 1;
	uint64_t n2 = 12;
	uint64_t n3 = 123;
	uint64_t n4 = 1234;
	uint64_t n5 = 12345;
	uint64_t n6 = 123456;
	uint64_t n7 = 1234567;
	uint64_t n8 = 12345678;
	uint64_t n9 = 123456789;
	uint64_t nA = 1234567890;
	uint64_t nB = 12345678901;
	uint64_t nC = 123456789012;
	uint64_t nD = 1234567890123;
	uint64_t nE = 12345678901234;
	uint64_t nF = 123456789012345;
	uint64_t nG = 1234567890123456;
	uint64_t nH = 12345678901234567;
	uint64_t nI = 123456789012345678;
	uint64_t nJ = 1234567890123456789;
	uint64_t nK = 123456789012345678901;
	uint64_t nM = 1234567890123456789012;

	printf("n1....: %s\n", bytes_resume(n1));
	printf("n2....: %s\n", bytes_resume(n2));
	printf("n3....: %s\n", bytes_resume(n3));
	printf("n4....: %s\n", bytes_resume(n4));
	printf("n5....: %s\n", bytes_resume(n5));
	printf("n6....: %s\n", bytes_resume(n6));
	printf("n7....: %s\n", bytes_resume(n7));
	printf("n8....: %s\n", bytes_resume(n8));
	printf("n9....: %s\n", bytes_resume(n9));
	printf("nA....: %s\n", bytes_resume(nA));
	printf("nB....: %s\n", bytes_resume(nB));
	printf("nC....: %s\n", bytes_resume(nC));
	printf("nD....: %s\n", bytes_resume(nD));
	printf("nE....: %s\n", bytes_resume(nE));
	printf("nF....: %s\n", bytes_resume(nF));
	printf("nG....: %s\n", bytes_resume(nG));
	printf("nH....: %s\n", bytes_resume(nH));
	printf("nI....: %s\n", bytes_resume(nI));
	printf("nJ....: %s\n", bytes_resume(nJ));
	printf("nK....: %s\n", bytes_resume(nK));
	printf("nM....: %s\n", bytes_resume(nM));
*/

/*
	printf("1....: %s\n", str_number_format(str1));
	printf("2....: %s\n", str_number_format(str2));
	printf("3....: %s\n", str_number_format(str3));
	printf("4....: %s\n", str_number_format(str4));
	printf("5....: %s\n", str_number_format(str5));
	printf("6....: %s\n", str_number_format(str6));
	printf("7....: %s\n", str_number_format(str7));
	printf("8....: %s\n", str_number_format(str8));
	printf("9....: %s\n", str_number_format(str9));
	printf("A....: %s\n", str_number_format(stra));
	printf("B....: %s\n", str_number_format(strb));
	printf("C....: %s\n", str_number_format(strc));
	printf("D....: %s\n", str_number_format(strd));
*/
	return 0;
}









