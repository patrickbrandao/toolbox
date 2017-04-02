
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



void help_str_onlychars(){
	printf("\n");
	printf("str_onlychars\n");
	printf("Retorna apenas os caracters permitidos sem uso de regex.\n");
	printf(" Parametros:\n");
	printf("    -n  : permite (0-9)\n");
	printf("    -l  : permite (a-z)\n");
	printf("    -L  : permite (A-Z)\n");
	printf("\n");
	printf("    -a  : permite (@)\n");
	printf("    -i  : permite (-)\n");
	printf("    -u  : permite (_)\n");
	printf("    -d  : permite (.)\n");
	printf("    -b  : permite espaco ( )\n");
	printf("    -S  : permite (\\)\n");
	printf("    -s  : permite (/)\n");
	printf("    -p  : permite (+)\n");
	printf("    -v  : permite (,)\n");
	printf("    -e  : permite (=)\n");
	printf("\n");
	printf("    -C  : permite (0-9, -, +)\n");
	printf("    -A  : permite (a-z, a-Z)\n");
	printf("    -X  : permite (a-z, A-Z, 0-9)\n");
	printf("    -N  : permite (espaco, a-z, A-Z, 0-9)\n");
	printf("    -U  : permite (a-z, A-Z, 0-9, _, ., -)\n");
	printf("    -K  : permite (a-z, A-Z, 0-9, _, ., -, @)\n");
	printf("    -D  : permite (a-z, A-Z, 0-9, _, ., -, /)\n");
	printf("\n");
	printf("    -q  : quieto, nao exibir resultado, apenas sinalizar se ha caracters proibidos\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: str_onlychars (sting) (opt) [opt] [opt]\n");
	printf("\n");
	exit(1);
}

#define WORD_END(chr)	(chr==',' || chr==';' || chr=='|' || chr=='/' || chr==' ' || chr=='\n' || chr=='\r' || chr=='\t')

//- int main(const int argc, const char **argv){
int main_str_onlychars(const char *progname, const int argc, const char **argv){
	char *input_string = NULL;
	int i = 0, input_len;


	char *new_string = NULL;
	int new_idx = 0, quiet = 0, invalids = 0;

	int have_azlower = 0,
		have_azupper = 0,
		have_numbers = 0,
		have_hiffem = 0,
		have_at = 0,
		have_underline = 0,
		have_space = 0,
		have_dot = 0,
		have_slash = 0,
		have_plus = 0,
		have_virg = 0,
		have_equal = 0,
		have_rslash = 0;

    if(argc<3) help_str_onlychars();

    // palavra
    input_string = strdup(argv[1]);
    input_len = strlen(input_string);
    if(!input_len) return 0;

    // coletar lista de caracters permitidos
    for(i = 2; i < argc; i++){
    	char optchr = argv[i][1];
    	if(!optchr) continue;
    	switch(optchr){
			case 'q': quiet = 1; break;

			case 'v': have_virg = 1; break;
			case 'e': have_equal = 1; break;
    		case 'p': have_plus = 1; break;
    		case 'n': have_numbers = 1; break;
			case 'l': have_azlower = 1; break;
			case 'L': have_azupper = 1; break;
			case 'A': have_azupper = 1; have_azlower = 1; break;
			case 'X': have_azupper = 1; have_azlower = 1; have_numbers = 1; break;

			case 'N': have_azupper = 1; have_azlower = 1; have_numbers = 1; have_space = 1; break;

			case 'C': have_plus = 1; have_hiffem = 1; have_numbers = 1; have_space = 1; break;

			case 'U': have_azupper = 1; have_azlower = 1; have_numbers = 1; have_underline = 1; have_dot = 1; have_hiffem = 1; break;
			case 'K': have_azupper = 1; have_azlower = 1; have_numbers = 1; have_underline = 1; have_dot = 1; have_hiffem = 1; have_at = 1; break;
			case 'D': have_azupper = 1; have_azlower = 1; have_numbers = 1; have_underline = 1; have_dot = 1; have_hiffem = 1; have_slash = 1; break;

    		case 'a': have_at = 1; break;
    		case 'u': have_underline = 1; break;
			case 'i': have_hiffem = 1; break;
			case 'd': have_dot = 1; break;
			case 'b': have_space = 1; break;
			case 's': have_slash = 1; break;
			case 'S': have_rslash = 1; break;

    	}
    }

    // nao ativou nada
    if( (have_azlower + have_azupper + have_numbers + have_space + have_underline + have_dot + have_slash + have_rslash + have_at + have_hiffem) < 1 ){
    	// usuaio nao quer nada?
    	if(quiet) return 4;
    	return 0;
    }

    // nova string
    new_string = (char*)malloc(input_len+1);
    bzero(new_string, input_len+1);

    // iniciar filtragem
    for(i=0; i < input_len; i++){

    	char ch = input_string[i];

		// letras minusculas
		if(ch >= 97 && ch <= 122 && have_azlower){ new_string[new_idx++] = ch; continue; }
		// letras maiusculas
		if(ch >= 65 && ch <= 90 && have_azupper){ new_string[new_idx++] = ch; continue; }

		// numero?
		if(ch >= 48 && ch <= 57 && have_numbers){ new_string[new_idx++] = ch; continue; }

		// underline?
		if(ch == '_' && have_underline){ new_string[new_idx++] = ch; continue; }

		// arroba?
		if(ch == '@' && have_at){ new_string[new_idx++] = ch; continue; }

		// hifem?
		if(ch == '-' && have_hiffem){ new_string[new_idx++] = ch; continue; }

		// espaco?
		if(ch == ' ' && have_space){ new_string[new_idx++] = ch; continue; }

		// ponto?
		if(ch == '.' && have_dot){ new_string[new_idx++] = ch; continue; }

		// barra?
		if(ch == '/' && have_slash){ new_string[new_idx++] = ch; continue; }

		// plus?
		if(ch == '+' && have_plus){ new_string[new_idx++] = ch; continue; }

		// virgula?
		if(ch == ',' && have_virg){ new_string[new_idx++] = ch; continue; }

		// igual?
		if(ch == '=' && have_equal){ new_string[new_idx++] = ch; continue; }

		// barra invertida?
		if(ch == '\\' && have_rslash){ new_string[new_idx++] = ch; continue; }

		// caracter proibido, ignora-lo
		invalids++;
    }

    // modo busca por invalidos
    if(quiet && invalids) return 3;
    if(quiet) return 0;

    // resultado
    printf("%s\n", new_string);

    // stdno de acordo com resultado (para ajudar na identificacao de caracter invalido)
    return new_idx ? 0 : 2;

}















