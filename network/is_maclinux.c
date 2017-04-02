
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>
#include <ctype.h>

// testar se string esta no formato ipv4
// porta na mesma declaracao
int is_maclinux(const char *str){
	int i, len;
	const char *maskstr = "xx:xx:xx:xx:xx:xx";
	const int masklen = 17;

	// string vazia
	if(!str || !str[0]) return 1;

	// tamanho
	len = strlen(str);
	if(len != masklen) return 2;

	// analisar string na mascara
	for(i=0; i < masklen; i++){
		char atch = str[i];
		char mkch = maskstr[i];
		if(mkch==':' && atch==':') continue;
		if(mkch=='x' && isxdigit(atch)) continue;
		return 3;
	}

	// tudo certo!
	return 0;
}

void help_is_maclinux(){
	printf("\n");
	printf("is_maclinux\n");
	printf("Verifica se os parametros estao no formato de um endereco MAC do linux\n");
	printf("Formato aceito: XX:XX:XX:XX:XX:XX\n");
	printf("\n");
	printf("Use: is_maclinux (mac-address)\n");
	printf("\n");
	exit(1);
}

int main_is_maclinux(const char *progname, const int argc, const char **argv){
//int main(const int argc, const char **argv){
    if(argc!=2) help_is_maclinux();
	int r = is_maclinux(argv[1]);
	return r;

}
















