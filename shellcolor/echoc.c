/*

	echo para exibir texto colorido ou formatadao
	-
*/

void help_echoc() {
	printf("Use: echoc -c (color) -b (bgcolor) [-n] [-l] [-B] [-s] [-p] [-k] [-N] TEXT\n" );
	printf("\t-B                bold text\n");
	printf("\t-s                sublinhed text\n");
	printf("\t-l                light text\n");
	printf("\t-n                don't break line after\n");
	printf("\t-k                keep colors after print text\n");
	printf("\t-p                blink text\n");
	printf("\t-L (number)       padding left spaces\n");
	printf("\t-R (number)       padding right spaces\n");
	printf("\t-K                bytes short format\n");
	printf("\t-N                number format\n");
	printf("\t-Y                convert to uppercase\n");
	printf("\t-W                convert to lowercase\n");
	printf("\t-c (color)        text color\n");
	printf("\t-b (color)        background color\n");
	printf("Colors list:\n");

	// exibicao de cores
	printf("\t");
	printf("%sred   %s ",     ANSI_VERMELHO, ANSI_RESET);
	printf("%sgreen   %s ",   ANSI_VERDE, ANSI_RESET);
	printf("%syellow   %s ",  ANSI_AMARELO, ANSI_RESET);
	printf("%sblue   %s ",    ANSI_AZUL, ANSI_RESET);
	printf("%spink   %s ",    ANSI_ROSA, ANSI_RESET);
	printf("%scyan   %s ",    ANSI_CIANO, ANSI_RESET);
	printf("%swhite   %s ",   ANSI_BRANCO, ANSI_RESET);
	printf("%slight   %s ",   ANSI_LIGHT, ANSI_RESET);
	printf("%sgray   %s ",    ANSI_PRETOL, ANSI_RESET);
	printf("%sblack   %s ",   ANSI_PRETO, ANSI_RESET);
	printf("\n\t");
	printf("%sred -l%s ",     ANSI_VERMELHOL, ANSI_RESET);
	printf("%sgreen -l%s ",   ANSI_VERDEL, ANSI_RESET);
	printf("%syellow -l%s ",  ANSI_AMARELOL, ANSI_RESET);
	printf("%sblue -l%s ",    ANSI_AZULL, ANSI_RESET);
	printf("%spink -l%s ",    ANSI_ROSAL, ANSI_RESET);
	printf("%scyan -l%s ",    ANSI_CIANOL, ANSI_RESET);
	printf("%swhite -l%s ",   ANSI_BRANCOL, ANSI_RESET);
	printf("\n");

	exit( 1 );

}

// principal
int main_echoc(const char *progname, const int argc, const char **argv){
	// variaveis
	register int outlen = 0;

	// texto e opcoes
	char *_output_string = NULL;

	//varivel para cor da fonte
	int  txtcolor = 0;

	// variavel para cor de fundo
	int bgcolor = 0;

	// flags especiais de cores de letra
	// -b = negrito
	// -s = sublinhado
	// -p = piscante
	int _text_effect = 0;
	int _light = 0;


	// quebrar linha apos exibir texto
	int _do_break = 1;

	// resetar cores do terminal apos terminar
	int _do_reset = 1;

	// espacamento
	int _left_space = 0;
	int _right_space = 0;

	// conversao de strings
	int _convert_case = 0; 	// 0 = nao alterar case, 1=upper, 2=lower

	// conversao para formato numerico
	//  0 = nao interpretar numero,
	//  1 = converter numero em bytes, exemplo: 19283 para 20 KBit
	//  2 = converter para formato numerico, exemplo: 123456 para 123.456
	int _to_number_format = 0;


	// processar argumentos do usuario
	#define TEST_COLOR(TEXT, VALUE)			if(strcmp(TEXT, argv[argn])==0){ argn++; if(cl) bgcolor = VALUE; else txtcolor = VALUE; continue; }

	int argn = 1;
	int cl = 0;
	while( argn < argc){

		// recebe argumentos
		cl = 0;

		// opcoes multi-parametros
		if( argn +1 < argc && (0==strcmp(argv[argn],"-c") || 0==strcmp(argv[argn],"-b")) ){
			if(0==strcmp(argv[argn],"-b")) cl=1;

			if(argn < argc) argn++; else continue;

			TEST_COLOR("blue", 5);
			TEST_COLOR("azul", 5);

			TEST_COLOR("red", 2);
			TEST_COLOR("vermelho", 2);

			TEST_COLOR("green", 3);
			TEST_COLOR("verde", 3);

			TEST_COLOR("magenta", 7);
			TEST_COLOR("celeste", 7);
			TEST_COLOR("cyan", 7);
			TEST_COLOR("cian", 7);

			TEST_COLOR("pink", 6);
			TEST_COLOR("rosa", 6);

			TEST_COLOR("yellow", 4);
			TEST_COLOR("amarelo", 4);

			TEST_COLOR("white", 8);
			TEST_COLOR("light", 9);
			TEST_COLOR("black", 1);

			TEST_COLOR("gray", 10);
			TEST_COLOR("cinza", 10);

			argn++;
		}

		// evitar sair do espaco de memoria
		if(argn >= argc) break;

		// definicao de espacamento
		// ESQUERDA
		if(strcmp(argv[argn],"-L") ==0 ){
			if(argn < argc) argn++; else continue;	
			// tamanho do espaco para alinhar a esquerda
			_left_space = atoi(argv[argn++]);
			if(_left_space < 0) _left_space = 0;
			continue;
		}
		// DIREITA
		if(strcmp(argv[argn],"-R") ==0 ){
			if(argn < argc) argn++; else continue;	
			// tamanho do espaco para alinhar a esquerda
			_right_space = atoi(argv[argn++]);
			if(_right_space < 0) _right_space = 0;
			continue;
		}

		// opcoes singulares
		if(0==strcmp(argv[argn],"-h") || 0==strcmp(argv[argn],"--help")){ help_echoc(); }
		if(0==strcmp(argv[argn],"-B")){ _text_effect = 1; ++argn; continue; }
		if(0==strcmp(argv[argn],"-s")){ _text_effect = 2; ++argn; continue; }
		if(0==strcmp(argv[argn],"-p")){ _text_effect = 3; ++argn; continue; }
		if(0==strcmp(argv[argn],"-l")){ _light = 1; ++argn; continue; }

		if(0==strcmp(argv[argn],"-n")){ _do_break = 2; ++argn; continue; }
		if(0==strcmp(argv[argn],"-k")){ _do_reset = 0; ++argn; continue; }

		// number
		if(0==strcmp(argv[argn],"-K")){ _to_number_format = 1; ++argn; continue; }
		if(0==strcmp(argv[argn],"-N")){ _to_number_format = 2; ++argn; continue; }

		// upper
		if(0==strcmp(argv[argn],"-Y")){ _convert_case = 1; ++argn; continue; }

		// lower
		if(0==strcmp(argv[argn],"-W")){ _convert_case = 2; ++argn; continue; }

		// texto
		if(strlen(argv[argn])) _output_string = strdup(argv[argn]);

		++argn;
	}
	if ( argn != argc ) help_echoc();



	//------------- argumentos prontos



	// evitar apontar para espaco nulo
	if(_output_string==NULL) _output_string = strdup("");

	// Definir coloracao
	if(txtcolor <= 9 && _light) txtcolor+= 9;
	printf("%s%s%s",background_colors[bgcolor], effects[_text_effect], text_colors[txtcolor]);

	// Processar texto de entrada
	if(_output_string) outlen = strlen(_output_string);

	// formatar case?
	if(outlen && _convert_case){
		if(_convert_case == 1) str_to_upper(_output_string);	// Maiusculas
		if(_convert_case == 2) str_to_lower(_output_string);	// Minusculas
	}

	// apenas numeros? formatar
	// bytes, resumir
	if(_to_number_format==1){
		uint64_t nbytes = 0;
		nbytes = uint64_t_atoi(_output_string);
		_output_string = strdup(bytes_resume(nbytes));
		outlen = strlen(_output_string);
	}
	// numeros separados por ponto
	if(_to_number_format==2){
		_output_string = str_number_format(_output_string);		// de 1234 para 1.234
		outlen = strlen(_output_string);
	}

	// fazer padding?
	if(_left_space){
		_output_string = str_pad_left(_output_string, _left_space);
	}else if(_right_space){
		_output_string = str_pad_right(_output_string, _right_space);
	}

// FINALIZAR -------------------------------------------------------------------------

	// jogar saida
	printf("%s", _output_string);

	// resetar cor
	if(_do_reset)
		printf("%s%s",background_colors[0],text_colors[0]);
	//-

	// quebra final de linha
	if(1==_do_break)
		printf("\n");
	//-

	// liberar memoria alocada nas formatacoes
	// MY_FREE();

	return 0;




}
































