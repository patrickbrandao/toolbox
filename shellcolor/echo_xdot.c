
/*

	echo para exibir texto colorido ou formatadao
	-
*/

void help_echo_xdot() {
	printf("Use: echo_xdot [opcoes] (0/1)\n" );
	printf("\t0                Exibe ponto (.)\n");
	printf("\t>0               Exibe x\n");
	printf("\tOpcoes:\n");
	printf("\t-b               Fazer quebra de linha no final\n");
	printf("\t-R               Nao resetar cor do caracter impresso\n");
	printf("\t-n               Repassar numero recebido na STDNO\n");
	exit(1);
}

// imprimir X
void echo_x(){ printf("%sx", ANSI_VERMELHO); }
void echo_x_reset(){ printf("%sx%s", ANSI_VERMELHO, ANSI_RESET); }

// imprimir .
void echo_dot(){ printf("%s.", ANSI_VERDE); }
void echo_dot_reset(){ printf("%s.%s", ANSI_VERDE, ANSI_RESET); }

// principal
int main_echo_xdot(const char *progname, const int argc, const char **argv){
	// 0 = ponto, 1 = x
	int mode = 0;
	int repass_stdno = 0;
	int input_number = 0;

	// quebrar linha apos exibir texto
	int _do_break = 0;

	// resetar cores do terminal apos terminar
	int _do_reset = 1;

	register int i = 0;
	int carg = 0, rarg = 0;
	
	// sem argumento, imprimir ponto sem quebra
	if(argc < 2){
		echo_dot_reset();
		return 0;
	}

	// Processar argumentos
	char ch;
	while ((ch = getopt(argc, (char * const*)argv, "nbRh?")) != EOF) {
		switch(ch) {
			// nao imprimir nova linha
			case 'n':
				repass_stdno = 1;
				carg++;
				break;

			// nao imprimir nova linha
			case 'b':
				_do_break = 1;
				carg++;
				break;

			// nao resetar
			case 'R':
				_do_reset = 0;
				carg++;
				break;

			case 'h':
			case '?':
			default:
				help_echo_xdot();
		}
	}

	// deve sobrar uma string
	rarg = (argc - carg) -1;

	// processar argumentos que restou
	if(rarg > 0 ){
		input_number = atoi(argv[carg+1]);
		if(input_number < 0) input_number = 0;
	}

	if(_do_reset){
		if(input_number) echo_x_reset(); else echo_dot_reset();
	}else{
		if(input_number) echo_x(); else echo_dot();
	}

	if(_do_break) printf("\n");

	// repassar stdno ?
	if(repass_stdno) return input_number;
	return 0;

}






