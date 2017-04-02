
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void help_in_list_like(){
	printf("Use: in_list_like (word) [item1] [item2] [...]\n");
	exit(1);
}

// 0 1 2
int main_in_list_like(const char *progname, const int argc, const char **argv){
	register int i = 0;
    if(argc<2) help_in_list_like();

    // passou a palavra sem argumentos, sem lista
    if(argc==2) return 1;

	for(i=2; i<argc; i++){
		int r = string_comp_nocase_like(argv[1], argv[i]);
		if(r > 0) return 0;
	}

	// nenhum item encontrado
	return 2;
}



















