
/*
	Criar barra de carregamento estatica

LABEL-SHORT [                                  50%                              ]
LABEL-LONG-LONG-LONG-LONG-LONG [                       50%                      ]
LABEL-LEN-FIXED           [                          50%                        ]
LABEL-MAX-LEN-MAX-LEN-MAX-LEN-MAX-LEN-MAX-LEN-MAX-LEN-MAX-MAX [       50%       ]

0123456789*         *         *         *         *         *         *         *
          10        20        30        40        50        60        70        80
          0123456789
                    0123456789
                              0123456789
                                        0123456789
                                                  0123456789
                                                            0123456789
                                                                      0123456789

	Cores a definir:
		LABEL 		Cor do texto
		BORDER 		Cor dos caracteres da borda
		FILL-FONT   Cor da fonte na parte preenchida
		FILL-BG     Cor do fundo na parte preenchida
		EMPTY-FONT  Cor da fonte na parte vazia
		EMPTY-BG    Cor do fundo na parte vazia

----------------------------------------------------------------------------------------------
Label.....................: maximo 60, minimo 0 significa ocultar label
Separacao label e loadin..: 1
Inicio borda..............: 1 [
Loadin com porcentagem....: (resto) [ 80 - 3 - strlen(label) ]
Fim borda.................: 1 ]
----------------------------------------------------------------------------------------------
*/

void help_shbar(){
	printf("Use: shbar -l (label) -v (value) [-n NUM -t TOTAL] [-d udelay] [-s style] [-r] [-b]");
	printf("\n");
	printf("Opcoes:\n");
	printf("    -l LABEL           Label anterior ao titulo\n");
	printf("    -v VALUE           Numero de porcentagem a exibir\n");
	printf("    -n NUM             Numero atual para calcular a porcentagem\n");
	printf("    -t TOTAL           Numero total para calcular a porcentagem\n");
	printf("    -w LABEL-SIZE      Usar tamanho fixo do label\n");
	printf("    -W LINE-SIZE       Tamanho total da linha (numero de colunas, padrao 80)\n");
	printf("    -b                 Efetuar quebra de linha apos concluir\n");
	printf("    -r                 Resetar ponteiro para inicio da linha apos concluir\n");
	printf("    -s STYLE           Numero do estilo:\n");

	printf("\t\t1:\n");
	//            3      4  5      6 7  8 9      a  b  c d e     f g                                         h i  j
	printf("\t\t%sLABEL%s %s[%s%s%s 15.%s%s79 %%                                   %s%s]%s\n",
		ANSI_CIANOL, ANSI_RESET,				// title 3 4
		ANSI_LIGHT, ANSI_RESET,					// border b c
		ANSI_BCIANO, ANSI_LIGHT,				// fill bg e font, d e
		ANSI_BAZUL, ANSI_CIANOL,				// empty bg e font, f g
		ANSI_RESET, ANSI_LIGHT, 				// zero bg e font, h, i
		ANSI_RESET    							// reset end, j
	);
	printf("\t\t2:\n");
	//            3      4  5      6 7  8 9      a  b  c d e     f g                                         h i  j
	printf("\t\t%sLABEL%s %s[%s%s%s 15.%s%s79 %%                                   %s%s]%s\n",
		ANSI_AMARELOL, ANSI_RESET,				// title 3 4
		ANSI_AMARELOL, ANSI_RESET,				// border b c
		ANSI_BVERMELHO, ANSI_VERMELHOL,			// fill bg e font, d e
		ANSI_BPRETO, ANSI_PRETOL,				// empty bg e font, f g
		ANSI_RESET, ANSI_AMARELOL,				// zero bg e font, h, i
		ANSI_RESET    							// reset end, j
	);
	printf("\t\t3:\n");
	//            3      4  5      6 7  8 9      a  b  c d e     f g                                         h i  j
	printf("\t\t%sLABEL%s %s[%s%s%s 15.%s%s79 %%                                   %s%s]%s\n",
		ANSI_VERDEL, ANSI_RESET,				// title 3 4
		ANSI_VERDEL, ANSI_RESET,				// border b c
		ANSI_BVERDE, ANSI_VERDEL,				// fill bg e font, d e
		ANSI_BPRETO, ANSI_PRETOL,				// empty bg e font, f g
		ANSI_RESET, ANSI_VERDEL,				// zero bg e font, h, i
		ANSI_RESET    							// reset end, j
	);
	printf("\t\t4:\n");
	//            3      4  5      6 7  8 9      a  b  c d e     f g                                         h i  j
	printf("\t\t%sLABEL%s %s[%s%s%s 15.%s%s79 %%                                   %s%s]%s\n",
		ANSI_AMARELOL, ANSI_RESET,				// title 3 4
		ANSI_AMARELOL, ANSI_RESET,				// border b c
		ANSI_BLARANJA, ANSI_LIGHT,				// fill bg e font, d e
		ANSI_BPRETO, ANSI_PRETOL,				// empty bg e font, f g
		ANSI_RESET, ANSI_AMARELOL,				// zero bg e font, h, i
		ANSI_RESET    							// reset end, j
	);
	printf("\t\t5:\n");
	//            3      4  5      6 7  8 9      a  b  c d e     f g                                         h i  j
	printf("\t\t%sLABEL%s %s[%s%s%s 15.%s%s79 %%                                   %s%s]%s\n",
		ANSI_ROSAL, ANSI_RESET,					// title 3 4
		ANSI_ROSAL, ANSI_RESET,					// border b c
		ANSI_BROSA, ANSI_LIGHT,					// fill bg e font, d e
		ANSI_BBRANCO, ANSI_PRETOL,				// empty bg e font, f g
		ANSI_RESET, ANSI_ROSAL,					// zero bg e font, h, i
		ANSI_RESET    							// reset end, j
	);
	printf("\t\t6:\n");
	//            3      4  5      6 7  8 9      a  b  c d e     f g                                         h i  j
	printf("\t\t%sLABEL%s %s[%s%s%s 15.%s%s79 %%                                   %s%s]%s\n",
		ANSI_CIANOL, ANSI_RESET,					// title 3 4
		ANSI_CIANOL, ANSI_RESET,					// border b c
		ANSI_BCIANO, ANSI_LIGHT,					// fill bg e font, d e
		ANSI_BBRANCO, ANSI_PRETOL,				// empty bg e font, f g
		ANSI_RESET, ANSI_CIANOL,					// zero bg e font, h, i
		ANSI_RESET    							// reset end, j
	);
	printf("\t\t7:\n");
	//            3      4  5      6 7  8 9      a  b  c d e     f g                                         h i  j
	printf("\t\t%sLABEL%s %s[%s%s%s 15.%s%s79 %%                                   %s%s]%s\n",
		ANSI_LIGHT, ANSI_RESET,				// title 3 4
		ANSI_LIGHT, ANSI_RESET,				// border b c
		ANSI_BBRANCO, ANSI_LIGHT,				// fill bg e font, d e
		ANSI_BPRETO, ANSI_PRETOL,				// empty bg e font, f g
		ANSI_RESET, ANSI_LIGHT,				// zero bg e font, h, i
		ANSI_RESET    							// reset end, j
	);
	printf("\t\t8:\n");
	//            3      4  5      6 7  8 9      a  b  c d e     f g                                         h i  j
	printf("\t\t%sLABEL%s %s[%s%s%s 15.%s%s79 %%                                   %s%s]%s\n",
		ANSI_AZUL, ANSI_RESET,				// title 3 4
		ANSI_LIGHT, ANSI_RESET,				// border b c
		ANSI_BAZUL, ANSI_LIGHT,				// fill bg e font, d e
		ANSI_BPRETO, ANSI_PRETOL,				// empty bg e font, f g
		ANSI_RESET, ANSI_LIGHT,				// zero bg e font, h, i
		ANSI_RESET    							// reset end, j
	);
	printf("\t\t9:\n");
	//            3      4  5      6 7  8 9      a  b  c d e     f g                                         h i  j
	printf("\t\t%sLABEL%s %s[%s%s%s 15.%s%s79 %%                                   %s%s]%s\n",
		ANSI_CIANOL, ANSI_RESET,				// title 3 4
		ANSI_LIGHT, ANSI_RESET,				// border b c
		ANSI_BCIANO, ANSI_LIGHT,				// fill bg e font, d e
		ANSI_BPRETO, ANSI_PRETOL,				// empty bg e font, f g
		ANSI_RESET, ANSI_LIGHT,				// zero bg e font, h, i
		ANSI_RESET    							// reset end, j
	);
	printf("\n");
	exit(1);
}

// finalizar programa ao receber sinal de morte
void shbar_interrupt(){
	// recuperar cursor
	TERMINAL_CURSOR(1);
	// pular para proxima linha
	printf("\n");
	// finalizar
	exit(0);
}

// calcular porcentagem
float shbar_percent(int count, int total){
	float pc = 0;
	float c = (float) count;
	float t = (float) total;

	// sem matematica para o obvio
	if(count >= total) return 100;
	if(!count || !total) return 0;

	// calcular pc
	pc = (float) ( (100 * c) / t );
	return pc;
}

#define LABELMAXSIZE 80
#define LINEMAXSIZE 160

int main_shbar(const char *progname, const int argc, const char **argv){

	int i = 0;
	int j = 0;
	int tmp1=0, tmp2=0, tmp3=0, tmp4=0;
	char tmpstr1[8];
	char *pstr1 = NULL, *pstr2 = NULL;

	// numero de caracteres impressos
	int printedlen = 0;

	char label[LABELMAXSIZE];
	int labellen = 0;

	// largura do texto e linha
	int labelsize = -1;
	int linesize = 80;
	int barsize = 0;			// tamanho da barra de carregamento, calculado, linesize - (labelsize + 3)

	// valores para porcentagem
	float fpercent = 0;			// porcentagem em float
	int ipercent = 0;			// porcentagem em inteiro
	int pcvalue = -1;			// numero de porcentagem pronto enviado pelo usuario
	int pcnumber = -1;			// valor atual relativo ao total
	int pctotal = -1;			// valor total
	int usedecimal = 0;			// usar 2 casas decimais?

	// estilo de cores
	int style = 0;

	// ativar debug
	int debug = 0;

	// cores
	char *color_label = NULL;
	char *color_border = NULL;
	char *color_fill_bg = NULL;
	char *color_fill_font = NULL;
	char *color_empty_bg = NULL;
	char *color_empty_font = NULL;

	// quebrar linha apos?
	int newline = 0;
	int rstline = 0;

	// buffer para criacao do texto a ser partido entre parte preenchida e parte vazia
	char loadinbar[LINEMAXSIZE];
	char loadinbar_on[LINEMAXSIZE];
	char loadinbar_off[LINEMAXSIZE];

	//----------------------------------------------------------------------------------------------- preparar variaveis, processar argumentos

	// espacos em branco no titulo
	bzero(label, LABELMAXSIZE);

	// processar argumentos
	char ch;
	while ((ch = getopt(argc, (char * const*)argv, "l:v:n:t:w:W:s:bdrh?")) != EOF) {
		switch(ch) {
			case 'd': debug = 1; break;
			case 'b': newline = 1; break;
			case 'r': rstline = 1; break;
			case 'l':
				labellen = strlen(optarg);
				if(labellen > LABELMAXSIZE-1) labellen = LABELMAXSIZE-1;
				strncpy(label, optarg, labellen);
				break;
			case 's': style = atoi(optarg); break;
			case 'n': pcnumber = atoi(optarg); break;
			case 't': pctotal = atoi(optarg); break;
			case 'v': pcvalue = atoi(optarg); break;
			case 'w': labelsize = atoi(optarg); break;
			case 'W': linesize = atoi(optarg); break;
			case 'h':
			case '?':
			default:
				help_shbar();
		}
	}

	// Ativar sinal de control+c para sair
	signal(SIGINT, shbar_interrupt);
	signal(SIGHUP, shbar_interrupt);
	signal(SIGQUIT, shbar_interrupt);
	signal(SIGABRT, shbar_interrupt);
	signal(SIGINT, shbar_interrupt);

	//----------------------------------------------------------------------------------------------- sanatizar valores

	// Calcular porcentagem a ser exibida
	if(pcvalue >= 0){
		// informou valor pronto
		if(pcvalue > 100) pcvalue = 100;
		fpercent = pcvalue;
		ipercent = pcvalue;
	}else{
		// nao informou valor pronto, calcular
		if(pcnumber < 0) pcnumber = 0;
		if(pctotal < 1) pctotal = 1;
		fpercent = shbar_percent(pcnumber, pctotal);
		ipercent = (int)fpercent;
		pcvalue = ipercent;
		usedecimal = 1;
	}

	// tamanho do label, fixo ou do tamanho do texto
	if(labelsize < 0) labelsize = strlen(label);

	// tamanho maximo da linha
	if(linesize < 10) linesize = 10;

	// tamanho da linha nao pode ser menor que [labelsize + 5]
	if(labelsize + 5 > linesize) linesize += 5;

	//-------------------------- inicio escolher estilo

		if(style < 1 || style > 9) style = 1;
		switch(style){
			case 1:
				color_label = ANSI_CIANOL;
				color_border = ANSI_LIGHT;
				color_fill_bg = ANSI_BCIANO;
				color_fill_font = ANSI_LIGHT;
				color_empty_bg = ANSI_BAZUL;
				color_empty_font = ANSI_CIANOL;
				break;

			case 2:
				color_label = ANSI_AMARELOL;
				color_border = ANSI_AMARELOL;
				color_fill_bg = ANSI_BVERMELHO;
				color_fill_font = ANSI_VERMELHOL;
				color_empty_bg = ANSI_BPRETO;
				color_empty_font = ANSI_PRETOL;
				break;

			case 3:
				color_label = ANSI_VERDEL;
				color_border = ANSI_VERDEL;
				color_fill_bg = ANSI_BVERDE;
				color_fill_font = ANSI_VERDEL;
				color_empty_bg = ANSI_BPRETO;
				color_empty_font = ANSI_PRETOL;
				break;

			case 4:
				color_label = ANSI_AMARELOL;
				color_border = ANSI_AMARELOL;
				color_fill_bg = ANSI_BLARANJA;
				color_fill_font = ANSI_LIGHT;
				color_empty_bg = ANSI_BPRETO;
				color_empty_font = ANSI_PRETOL;
				break;

			case 5:
				color_label = ANSI_ROSAL;
				color_border = ANSI_ROSAL;
				color_fill_bg = ANSI_BROSA;
				color_fill_font = ANSI_LIGHT;
				color_empty_bg = ANSI_BBRANCO;
				color_empty_font = ANSI_PRETOL;
				break;

			case 6:
				color_label = ANSI_CIANOL;
				color_border = ANSI_CIANOL;
				color_fill_bg = ANSI_BCIANO;
				color_fill_font = ANSI_LIGHT;
				color_empty_bg = ANSI_BBRANCO;
				color_empty_font = ANSI_PRETOL;
				break;

			case 7:
				color_label = ANSI_LIGHT;
				color_border = ANSI_LIGHT;
				color_fill_bg = ANSI_BBRANCO;
				color_fill_font = ANSI_LIGHT;
				color_empty_bg = ANSI_BPRETO;
				color_empty_font = ANSI_PRETOL;
				break;

			case 8:
				color_label = ANSI_AZUL;
				color_border = ANSI_LIGHT;
				color_fill_bg = ANSI_BAZUL;
				color_fill_font = ANSI_LIGHT;
				color_empty_bg = ANSI_BPRETO;
				color_empty_font = ANSI_PRETOL;
				break;

			case 9:
				color_label = ANSI_CIANOL;
				color_border = ANSI_LIGHT;
				color_fill_bg = ANSI_BCIANO;
				color_fill_font = ANSI_LIGHT;
				color_empty_bg = ANSI_BPRETO;
				color_empty_font = ANSI_PRETOL;
				break;

		}

	//--------------------------> Criar barra

	// voltar ao inicio da linha
	printf("\r");

	//############## Label
	if(labelsize){
		if(labellen){
			// label informado

			// truncar label caso o espaco ordenado seja menor
			if(labellen > labelsize){
				// obedecer labelsize
				labellen = labelsize;
				label[labellen] = '\0';
			}

			printf("%s%s%s%s", ANSI_RESET, color_label, label, ANSI_RESET);
			printedlen += labellen;
			if(printedlen < labelsize) for(i=0;i < labelsize-printedlen; i++) printf(" ");
		}else{
			// label ausente, setou tamanho mas nao informou o texto
			for(i=0; i < labelsize; i++) printf(" ");
			printedlen += labelsize;
		}

		//############## caracter separador
		if(labelsize==labellen){ printf(" "); printedlen++; }

	}


	//############## borda 1
	printf("%s[", color_border);
	printedlen++;

	//############## barra de carregamento
		// limpar buffer de trabalho
		bzero(loadinbar, LINEMAXSIZE);
		bzero(loadinbar_on, LINEMAXSIZE);
		bzero(loadinbar_off, LINEMAXSIZE);

		// encher de espacos
		for(i=0; i < LINEMAXSIZE-1; i++) loadinbar[i] = ' ';
		bzero(tmpstr1, 8);

		// montar string da barra (restante da linha, deixar 1 byte para fechamento)
		//barsize = linesize - printedlen - 1;
		barsize = linesize - (labelsize + 3);
		if(barsize < 10) barsize = 10;

		// caracteres a afastar da esquerda
		// colocar porcentagem no meio recuando 3 bytes
		tmp1 = (barsize / 2) - 3;

		// obter numero da porcentagem em inteiro
		if(usedecimal){
			sprintf(tmpstr1, "%6.2f %%", fpercent);
		}else{
			sprintf(tmpstr1, "%d %%", ipercent);
			// nao perdemos 4 bytes dos decimais, avancar para alinhar
			tmp1+=2;
		}

		// copiar valor numerico para o meio da barra
		tmp2 = strlen(tmpstr1);
		strncpy (loadinbar+tmp1, tmpstr1, tmp2);

		// encerrar barra de carregamento no buffer
		loadinbar[barsize] = '\0';

		// gerar copias da barra pronta
		strcpy(loadinbar_on, loadinbar);
		strcpy(loadinbar_off, loadinbar);
		pstr1 = loadinbar_on;
		pstr2 = loadinbar_off;

		// obter numero de bytes que representam a porcentagem corrente (ocupada)
		tmp3 = (int)((ipercent * barsize) / 100);
		tmp4 = barsize - tmp3;

		// encerrar primeiro buffer em x caracteres apartir de tmp3
		if(tmp3){
			pstr1[tmp3] = '\0';
			printf("%s%s%s%s", ANSI_RESET, color_fill_bg, color_fill_font, pstr1);

			// avancar no buffer apagado o mesmo numero de caracteres que imprimimos aqui
			for(i=0; i< tmp3; i++) pstr2++;

			// exibir restante livre, se houver espaco sobrando
			if(tmp4) printf("%s%s%s%s", ANSI_RESET, color_empty_bg, color_empty_font, pstr2);

		}else{
			// nao existe parte, tudo livre
			printf("%s%s%s%s", ANSI_RESET, color_empty_bg, color_empty_font, pstr1);
		}

	//############## borda 2
	printf("%s%s]%s", ANSI_RESET, color_border, ANSI_RESET);
	//printf("%s%s]%s tmp3=%d tmp4=%d barsize=%d linesize=%d", ANSI_RESET, color_border, ANSI_RESET, tmp3, tmp4, barsize, linesize);
	printedlen++;

	//--------------------------> DEBUG
	if(debug){
		printf("\n");
		printf("0123456789abcdefghij0123456789abcdefghij0123456789abcdefghij\n");
		printf("\n");
		printf("LABEL..............: [%s]\n", label);
		printf("LABEL-LENGHT.......: [%d]\n", labellen);
		printf("LABEL-SIZE.........: [%d]\n", labelsize);
		printf("LINE-SIZE..........: [%d]\n", linesize);
		printf("BAR-SIZE...........: [%d]\n", barsize);
		printf("LINEMAXSIZE........: [%d]\n", LINEMAXSIZE);
		printf("LOADINBAR..........: [%s]\n", loadinbar);
		printf("TMP INTs...........: j[%d] tmp1[%d] tmp2[%d] tmp3[%d] tmp4[%d]\n", j, tmp1, tmp2, tmp3, tmp4);
		printf("TMP STRs...........: [%s]\n", tmpstr1);
		printf("P-STR 1............: [%s]\n", pstr1);
		printf("P-STR 2............: [%s]\n", pstr2);
		printf("loadinbar_on.......: [%s]\n", loadinbar_on);
		printf("loadinbar_off......: [%s]\n", loadinbar_off);
		printf("PC-VALUE...........: [%d]\n", pcvalue);
		printf("PC-NUMBER..........: [%d]\n", pcnumber);
		printf("PC-TOTAL...........: [%d]\n", pctotal);
		printf("STYLE..............: [%d]\n", style);
		printf("NEWLINE............: [%d]\n", newline);
		printf("RESET-LINE.........: [%d]\n", rstline);
		printf("Cores:\n");
		printf("%s%sCOLOR-LABEL%s\n", ANSI_RESET, color_label, ANSI_RESET);
		printf("%s%sCOLOR-BORDER%s\n", ANSI_RESET, color_border, ANSI_RESET);
		printf("%s%s%sFILL-BG-FONTE%s\n", ANSI_RESET, color_fill_bg, color_fill_font, ANSI_RESET);
		printf("%s%s%sEMPTY-BG-FONTE%s\n", ANSI_RESET, color_empty_bg, color_empty_font, ANSI_RESET);
		printf("\n");
	}
	//--------------------------> FIM

	// nova linha
	if(newline) printf("\n");

	// voltar ao inicio da linha?
	if(rstline || !newline) printf("\r");

	// ativar cursor novamente
	TERMINAL_CURSOR(1);

	return 0;
}


