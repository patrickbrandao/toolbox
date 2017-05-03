
/*
----------------------------------------------------------------------------------------------
Comprimindo baselinux-1.0.txz -----/..... [                                                  ]
----------------------------------------------------------------------------------------------
01234567890123456789
                    x
                     012345678901234567890123456789
                                                   x-----/.....
                                                               < espaco fixo
                                                               x
                                                                [                            ]
                                                                [ 28.91 %                    ]
----------------------------------------------------------------------------------------------
Label.......: maximo 20
Title.......: maximo 20
Contador....: 11 bytes, 5 para contagem, um /, 5 para o maximo
Barra.......: restante, 1 byte para '[', barra, 1 bytes para ']'
----------------------------------------------------------------------------------------------
*/

void help_shloading(){
	printf("Use: ./youscript | shloading -l (pre-label) -t (title) -m (total-lines) [-s style] [-d udelay] [-n]");
	printf("\n");
	printf("Opcoes:\n");
	printf("    -n                 Nao efetuar quebra de linha apos concluir\n");
	printf("    -c                 Limpar linha apos concluir\n");
	printf("    -l LABEL           Label anterior ao titulo\n");
	printf("    -t TITLE           Titulo (posterior ao label)\n");
	printf("    -m TOTAL           Numero total de linhas esperadas no STDIN\n");
	printf("    -d DELAY           Induzir delay em micro-segundos entre linhas do STDIN\n");
	printf("    -s STYLE           Numero do estilo:\n");

	printf("\t\t1:\n");
	//       1      2  3      4  5      6 7  8 9      a  b  c d e     f g                                         h i  j
	printf("\t\t%sLabel%s %stitle%s %s-----%s%s/%s%s.....%s %s[%s%s%s 15.%s%s79 %%                                   %s%s]%s\n",
		ANSI_LIGHT, ANSI_RESET,					// label 1 2
		ANSI_CIANOL, ANSI_RESET,				// title 3 4
		ANSI_PRETOL, ANSI_RESET,				// count 5 6
		ANSI_LIGHT, ANSI_RESET,					// border: / 7 8
		ANSI_BRANCO, ANSI_RESET,				// total 9 a
		ANSI_LIGHT, ANSI_RESET,					// border b c
		ANSI_BCIANO, ANSI_CIANOL,				// fill bg e font, d e
		ANSI_BAZUL, ANSI_AZULL,					// empty bg e font, f g
		ANSI_RESET, ANSI_LIGHT, 				// zero bg e font, h, i
		ANSI_RESET    							// reset end, j
	);
	printf("\t\t2:\n");
	//       1      2  3      4  5      6 7  8 9      a  b  c d e     f g                                         h i  j
	printf("\t\t%sLabel%s %stitle%s %s-----%s%s/%s%s.....%s %s[%s%s%s 15.%s%s79 %%                                   %s%s]%s\n",
		ANSI_LIGHT, ANSI_RESET,				// label 1 2
		ANSI_AMARELOL, ANSI_RESET,				// title 3 4
		ANSI_PRETOL, ANSI_RESET,				// count 5 6
		ANSI_AMARELOL, ANSI_RESET,				// border: / 7 8
		ANSI_PRETOL, ANSI_RESET,				// total 9 a
		ANSI_AMARELOL, ANSI_RESET,				// border b c
		ANSI_BVERMELHO, ANSI_VERMELHOL,			// fill bg e font, d e
		ANSI_BPRETO, ANSI_PRETOL,				// empty bg e font, f g
		ANSI_RESET, ANSI_AMARELOL,				// zero bg e font, h, i
		ANSI_RESET    							// reset end, j
	);
	printf("\t\t3:\n");
	//       1      2  3      4  5      6 7  8 9      a  b  c d e     f g                                         h i  j
	printf("\t\t%sLabel%s %stitle%s %s-----%s%s/%s%s.....%s %s[%s%s%s 15.%s%s79 %%                                   %s%s]%s\n",
		ANSI_LIGHT, ANSI_RESET,					// label 1 2
		ANSI_VERDEL, ANSI_RESET,				// title 3 4
		ANSI_PRETOL, ANSI_RESET,				// count 5 6
		ANSI_VERDEL, ANSI_RESET,				// border: / 7 8
		ANSI_BRANCO, ANSI_RESET,				// total 9 a
		ANSI_VERDEL, ANSI_RESET,				// border b c
		ANSI_BVERDE, ANSI_VERDEL,				// fill bg e font, d e
		ANSI_BPRETO, ANSI_PRETOL,				// empty bg e font, f g
		ANSI_RESET, ANSI_VERDEL,				// zero bg e font, h, i
		ANSI_RESET    							// reset end, j
	);
	printf("\t\t4:\n");
	//       1      2  3      4  5      6 7  8 9      a  b  c d e     f g                                         h i  j
	printf("\t\t%sLabel%s %stitle%s %s-----%s%s/%s%s.....%s %s[%s%s%s 15.%s%s79 %%                                   %s%s]%s\n",
		ANSI_LIGHT, ANSI_RESET,				// label 1 2
		ANSI_AMARELOL, ANSI_RESET,				// title 3 4
		ANSI_PRETOL, ANSI_RESET,				// count 5 6
		ANSI_AMARELOL, ANSI_RESET,				// border: / 7 8
		ANSI_BRANCO, ANSI_RESET,				// total 9 a
		ANSI_AMARELOL, ANSI_RESET,				// border b c
		ANSI_BLARANJA, ANSI_LIGHT,				// fill bg e font, d e
		ANSI_BPRETO, ANSI_PRETOL,				// empty bg e font, f g
		ANSI_RESET, ANSI_AMARELOL,				// zero bg e font, h, i
		ANSI_RESET    							// reset end, j
	);
	printf("\t\t5:\n");
	//       1      2  3      4  5      6 7  8 9      a  b  c d e     f g                                         h i  j
	printf("\t\t%sLabel%s %stitle%s %s-----%s%s/%s%s.....%s %s[%s%s%s 15.%s%s79 %%                                   %s%s]%s\n",
		ANSI_LIGHT, ANSI_RESET,					// label 1 2
		ANSI_ROSAL, ANSI_RESET,					// title 3 4
		ANSI_PRETOL, ANSI_RESET,				// count 5 6
		ANSI_ROSAL, ANSI_RESET,					// border: / 7 8
		ANSI_BRANCO, ANSI_RESET,				// total 9 a
		ANSI_ROSAL, ANSI_RESET,					// border b c
		ANSI_BROSA, ANSI_LIGHT,					// fill bg e font, d e
		ANSI_BBRANCO, ANSI_PRETOL,				// empty bg e font, f g
		ANSI_RESET, ANSI_ROSAL,					// zero bg e font, h, i
		ANSI_RESET    							// reset end, j
	);
	printf("\t\t6:\n");
	//       1      2  3      4  5      6 7  8 9      a  b  c d e     f g                                         h i  j
	printf("\t\t%sLabel%s %stitle%s %s-----%s%s/%s%s.....%s %s[%s%s%s 15.%s%s79 %%                                   %s%s]%s\n",
		ANSI_LIGHT, ANSI_RESET,					// label 1 2
		ANSI_CIANOL, ANSI_RESET,					// title 3 4
		ANSI_PRETOL, ANSI_RESET,				// count 5 6
		ANSI_CIANOL, ANSI_RESET,					// border: / 7 8
		ANSI_BRANCO, ANSI_RESET,				// total 9 a
		ANSI_CIANOL, ANSI_RESET,					// border b c
		ANSI_BCIANO, ANSI_LIGHT,					// fill bg e font, d e
		ANSI_BBRANCO, ANSI_PRETOL,				// empty bg e font, f g
		ANSI_RESET, ANSI_CIANOL,					// zero bg e font, h, i
		ANSI_RESET    							// reset end, j
	);
	printf("\t\t7:\n");
	//       1      2  3      4  5      6 7  8 9      a  b  c d e     f g                                         h i  j
	printf("\t\t%sLabel%s %stitle%s %s-----%s%s/%s%s.....%s %s[%s%s%s 15.%s%s79 %%                                   %s%s]%s\n",
		ANSI_LIGHT, ANSI_RESET,				// label 1 2
		ANSI_LIGHT, ANSI_RESET,				// title 3 4
		ANSI_PRETOL, ANSI_RESET,				// count 5 6
		ANSI_LIGHT, ANSI_RESET,				// border: / 7 8
		ANSI_BRANCO, ANSI_RESET,				// total 9 a
		ANSI_LIGHT, ANSI_RESET,				// border b c
		ANSI_BBRANCO, ANSI_LIGHT,				// fill bg e font, d e
		ANSI_BPRETO, ANSI_PRETOL,				// empty bg e font, f g
		ANSI_RESET, ANSI_LIGHT,				// zero bg e font, h, i
		ANSI_RESET    							// reset end, j
	);
	printf("\t\t8:\n");
	//       1      2  3      4  5      6 7  8 9      a  b  c d e     f g                                         h i  j
	printf("\t\t%sLabel%s %stitle%s %s-----%s%s/%s%s.....%s %s[%s%s%s 15.%s%s79 %%                                   %s%s]%s\n",
		ANSI_LIGHT, ANSI_RESET,				// label 1 2
		ANSI_AZUL, ANSI_RESET,				// title 3 4
		ANSI_PRETOL, ANSI_RESET,				// count 5 6
		ANSI_LIGHT, ANSI_RESET,				// border: / 7 8
		ANSI_BRANCO, ANSI_RESET,				// total 9 a
		ANSI_LIGHT, ANSI_RESET,				// border b c
		ANSI_BAZUL, ANSI_LIGHT,				// fill bg e font, d e
		ANSI_BPRETO, ANSI_PRETOL,				// empty bg e font, f g
		ANSI_RESET, ANSI_LIGHT,				// zero bg e font, h, i
		ANSI_RESET    							// reset end, j
	);
	printf("\t\t9:\n");
	//       1      2  3      4  5      6 7  8 9      a  b  c d e     f g                                         h i  j
	printf("\t\t%sLabel%s %stitle%s %s-----%s%s/%s%s.....%s %s[%s%s%s 15.%s%s79 %%                                   %s%s]%s\n",
		ANSI_LIGHT, ANSI_RESET,				// label 1 2
		ANSI_CIANOL, ANSI_RESET,				// title 3 4
		ANSI_PRETOL, ANSI_RESET,				// count 5 6
		ANSI_LIGHT, ANSI_RESET,				// border: / 7 8
		ANSI_BRANCO, ANSI_RESET,				// total 9 a
		ANSI_LIGHT, ANSI_RESET,				// border b c
		ANSI_BCIANO, ANSI_LIGHT,				// fill bg e font, d e
		ANSI_BPRETO, ANSI_PRETOL,				// empty bg e font, f g
		ANSI_RESET, ANSI_LIGHT,				// zero bg e font, h, i
		ANSI_RESET    							// reset end, j
	);
	printf("\n");

	printf("\n");
	exit(1);
}

// finalizar programa ao receber sinal de morte
void shloading_interrupt(){
	// recuperar cursor
	TERMINAL_CURSOR(1);
	// pular para proxima linha
	printf("\n");
	// finalizar
	exit(0);
}

// calcular porcentagem
float shloading_percent(int count, int total){
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

int main_shloading(const char *progname, const int argc, const char **argv){

	//----------------------------------------------------------------------------------------------- declarar variaveis

	char label[31]; int llen = 0;
	char title[31]; int tlen = 0;

	// largura do texto
	int fixlen = 0;

	// espaco da barra
	int barlen = 0;
	char barbuf[81];
	char bar_fill[81];
	char bar_zero[81];
	// ponteiros dos buffers da barra
	char *p1 = bar_fill, *p2 = bar_zero;

	int style = 0;		// estilo de cores
	int line_count = 0; // numero de linhas recebidas
	int line_total = 0; // total de linhas a processar

	// contador de ping-pong quando nao temos um total
	int pingpong = 1;

	// conteudo do stdin
	char *line = NULL;
	size_t size;

	// cores
	char *color_stitle = NULL;
	char *color_slabel = NULL;
	char *color_count = NULL;
	char *color_total = NULL;
	char *color_border = NULL;
	char *color_fill_bg = NULL;
	char *color_fill_font = NULL;
	char *color_empty_bg = NULL;
	char *color_empty_font = NULL;

	//----------------------------------------------------------------------------------------------- preparar variaveis, processar argumentos

	// espacos em branco no titulo
	bzero(title, 31);
	bzero(label, 31);
	bzero(barbuf, 81);
	bzero(bar_fill, 81);
	bzero(bar_zero, 81);

	// quebrar linha apos?
	int newline = 1;
	int clsline = 0;

	// demorar entre analises de proposito?
	int udelay = 0;

	// processar argumentos
	char ch;
	while ((ch = getopt(argc, (char * const*)argv, "l:t:m:s:d:nch?")) != EOF) {
		switch(ch) {
			case 'n':
				newline = 0;
				break;
			case 'c':
				clsline = 1;
				break;
			case 'l':
				strncpy(label, optarg, 30);
				break;

			case 't':
				strncpy(title, optarg, 30);
				break;

			case 's':
				style = atoi(optarg);
				break;				

			case 'm':
				line_total = atoi(optarg);
				break;				
			case 'd':
				udelay = atoi(optarg);
				break;				

			case 'h':
			case '?':
			default:
				help_shloading();
		}
	}

	// Ativar sinal de control+c para sair
	signal(SIGINT, shloading_interrupt);
	signal(SIGHUP, shloading_interrupt);
	signal(SIGQUIT, shloading_interrupt);
	signal(SIGABRT, shloading_interrupt);
	signal(SIGINT, shloading_interrupt);

	//----------------------------------------------------------------------------------------------- sanatizar valores

	// DELAY
	// nao pode ser negativo
	if(udelay < 0) udelay = 0;
	// nao pode ser muito tempo, maximo 100 segundos
	if(udelay > 100000000) udelay = 100000000;

	//-------------------------- inicio escolher estilo

		if(style < 1 || style > 9) style = 1;
		switch(style){
			case 1:
				color_stitle = ANSI_LIGHT;
				color_slabel = ANSI_CIANOL;
				color_count = ANSI_PRETOL;
				color_total = ANSI_BRANCO;
				color_border = ANSI_LIGHT;
				color_fill_bg = ANSI_BCIANO;
				color_fill_font = ANSI_CIANOL;
				color_empty_bg = ANSI_BAZUL;
				color_empty_font = ANSI_AZULL;
				break;

			case 2:
				color_stitle = ANSI_VERMELHOL;
				color_slabel = ANSI_AMARELOL;
				color_count = ANSI_PRETOL;
				color_total = ANSI_PRETOL;
				color_border = ANSI_AMARELOL;
				color_fill_bg = ANSI_BVERMELHO;
				color_fill_font = ANSI_VERMELHOL;
				color_empty_bg = ANSI_BPRETO;
				color_empty_font = ANSI_PRETOL;
				break;

			case 3:
				color_stitle = ANSI_LIGHT;
				color_slabel = ANSI_VERDEL;
				color_count = ANSI_PRETOL;
				color_total = ANSI_BRANCO;
				color_border = ANSI_VERDEL;
				color_fill_bg = ANSI_BVERDE;
				color_fill_font = ANSI_VERDEL;
				color_empty_bg = ANSI_BPRETO;
				color_empty_font = ANSI_PRETOL;
				break;

			case 4:
				color_stitle = ANSI_LIGHT;
				color_slabel = ANSI_AMARELOL;
				color_count = ANSI_PRETOL;
				color_total = ANSI_BRANCO;
				color_border = ANSI_AMARELOL;
				color_fill_bg = ANSI_BLARANJA;
				color_fill_font = ANSI_LIGHT;
				color_empty_bg = ANSI_BPRETO;
				color_empty_font = ANSI_PRETOL;
				break;

			case 5:
				color_stitle = ANSI_LIGHT;
				color_slabel = ANSI_ROSAL;
				color_count = ANSI_PRETOL;
				color_total = ANSI_BRANCO;
				color_border = ANSI_ROSAL;
				color_fill_bg = ANSI_BROSA;
				color_fill_font = ANSI_LIGHT;
				color_empty_bg = ANSI_BBRANCO;
				color_empty_font = ANSI_PRETOL;
				break;

			case 6:
				color_stitle = ANSI_LIGHT;
				color_slabel = ANSI_CIANOL;
				color_count = ANSI_PRETOL;
				color_total = ANSI_BRANCO;
				color_border = ANSI_CIANOL;
				color_fill_bg = ANSI_BCIANO;
				color_fill_font = ANSI_LIGHT;
				color_empty_bg = ANSI_BBRANCO;
				color_empty_font = ANSI_PRETOL;
				break;

			case 7:
				color_stitle = ANSI_LIGHT;
				color_slabel = ANSI_LIGHT;
				color_count = ANSI_PRETOL;
				color_total = ANSI_BRANCO;
				color_border = ANSI_LIGHT;
				color_fill_bg = ANSI_BBRANCO;
				color_fill_font = ANSI_LIGHT;
				color_empty_bg = ANSI_BPRETO;
				color_empty_font = ANSI_PRETOL;
				break;

			case 8:
				color_stitle = ANSI_LIGHT;
				color_slabel = ANSI_AZUL;
				color_count = ANSI_PRETOL;
				color_total = ANSI_BRANCO;
				color_border = ANSI_LIGHT;
				color_fill_bg = ANSI_BAZUL;
				color_fill_font = ANSI_LIGHT;
				color_empty_bg = ANSI_BPRETO;
				color_empty_font = ANSI_PRETOL;
				break;

			case 9:
				color_stitle = ANSI_LIGHT;
				color_slabel = ANSI_CIANOL;
				color_count = ANSI_PRETOL;
				color_total = ANSI_BRANCO;
				color_border = ANSI_LIGHT;
				color_fill_bg = ANSI_BCIANO;
				color_fill_font = ANSI_LIGHT;
				color_empty_bg = ANSI_BPRETO;
				color_empty_font = ANSI_PRETOL;
				break;

		}

	//-------------------------- fim escolher estilo


	// tamanho dos textos
	tlen = strlen(title);
	llen = strlen(label);

	// titulo tem preferencia
	// acima de 30 bytes retiraremos o label, limite sera 41 bytes
	if(tlen>30){
		// retirar label
		llen = 0;
		// nao extrapolar 41 bytes (41 por temos o espaco do label, o divisor e o espaco do titulo)
		if(tlen>41) tlen=41;
	}
	// label nao pode ser menor que 20, salvo se houver espaco nos primeiro 40 bytes
	if(llen>20){

		// estrapolou
		if(llen+tlen > 41) llen = 0;
	}

	// tamanho dos labels prontos

	// ajustar label
	if(llen){
		// espaco dividor
		label[llen] = ' ';
		// fim
		label[llen+1] = 0;
		fixlen += llen + 1;
		
	}

	// ajustar titulo
	if(tlen){
		// espaco dividor
		title[tlen] = ' ';
		// fim
		title[tlen+1] = 0;
		fixlen += tlen + 1;
	}

	//----------------------------------------------------------------------------------------------- montar barra

	// calcular tamanho da barra,
	// considerando que temos em fixlen a quantidade de bytes consumidos e precisamos de 
	// 11 bytes para o contador, 1 bytes para separacao, 2 bytes de chaves '[]''
	barlen = (80 - (fixlen + 1 + 11 + 2));

	// DEBUG
	// printf("Title....: [%s] (%d)\n", title, tlen);
	// printf("Label....: [%s] (%d)\n", label, llen);
	//printf("Style....: (%d)\n", style);
	// printf("   barlen: %d\n", barlen);
	// printf("TOTAL: %d\n", line_total);

	// Limpar e resetar linha
	TERMINAL_CLSLINER();
	// ocultar cursor
	TERMINAL_CURSOR(0);

	// ler stdin linha-a-linha
	while(getline(&line, &size, stdin) != -1){
		
		int w;
		int ipercent = 0;
		float fpercent = 0;

		// bytes ocupados
		int barcollen = 0;

		// bytes livres
		int barcolres = 0;

		// incrementar linha processada
		line_count++;

		TERMINAL_RETURN();


		// Desenhar parte fixa
			// label
			if(llen) printf("%s%s%s", color_stitle, label, ANSI_RESET);
			// titulo
			if(tlen) printf("%s%s%s", color_slabel, title, ANSI_RESET);

			// contadores: -----/.....
			printf("%s%5d%s%s/%s%s%5d%s ", color_count, line_count, ANSI_RESET, color_border, ANSI_RESET, color_total, line_total, ANSI_RESET);

		//-

		// calcular porcentagem do total
		fpercent = shloading_percent(line_count, line_total);
		ipercent = (int) fpercent;

		// obter porcentagem de ocupacao da barra
		barcollen = (int) ( ( barlen * ipercent ) / 100 );

		// criar barra, cheia de espacos e com final apos o tamanho maximo
			bspace(barbuf, 80);
			if(line_total){
				w = sprintf(barbuf, " %6.2f %%", fpercent);
			}else{

				barcollen = pingpong;
				pingpong++;
				if(pingpong >= barlen) pingpong = 1;

				w = sprintf(barbuf, " %i / %i / %i | %i", line_count, barlen, barcollen, pingpong);
				// barcollen = pingpong;
			}

			// fechamento de seguranca
			barbuf[80] = 0;

			// nao fechar string apos sprintf, deixar com 80 bytes
			if(w && w <= 80) barbuf[w] = ' ';

		// calcular espaco restante na barra
		barcolres = barlen - barcollen;


		// parte clara - copiar para bar_fill apenas a parte escura, nao precisamos fechar pois bar_fill e' puro zeros
		if(barcollen) strncpy(bar_fill, barbuf, barcollen);

		// parte escura - devemos iniciar na posicao posterior a parte clara, e obter os bytes que sobraram
		bzero(bar_zero, 81);
		if(barcolres){
			char *bp = (barbuf)+(barcollen);
			//      .         .posicao inicial    .copiar apenas bytes para preencher o que resta
			strncpy(bar_zero, barbuf+barcollen, barcolres);
			//printf(" > set bar_zero position=%p barcolres=%d\n", bp, barcolres);
		}

		// Desenhar barra de carregamento
			printf("%s[%s", color_border, ANSI_RESET );

			// exibir parte clara
			//!if(barcollen) printf("%s%s%s%s", color_fill_bg, color_fill_font, p1, ANSI_RESET );

			// exibir parte escura
			//!if(barcolres) printf("%s%s%s%s", color_empty_bg, color_empty_font, p2, ANSI_RESET );

			// MODO PORCENTAGEM
			if(line_total){

				// exibir parte clara
				if(barcollen) printf("%s%s%s%s", color_fill_bg, color_fill_font, p1, ANSI_RESET );

				// exibir parte escura
				if(barcolres) printf("%s%s%s%s", color_empty_bg, color_empty_font, p2, ANSI_RESET );

			}else{
			// MODO PING-PONG

				// exibir parte clara
				if(barcollen) printf("%s%s%s%s", color_fill_bg, color_fill_font, p1, ANSI_RESET );

				// exibir parte escura
				if(barcolres) printf("%s%s%s%s", color_empty_bg, color_empty_font, p2, ANSI_RESET );

			}

			// fechar barra de carregamento			
			printf("%s]%s", color_border, ANSI_RESET );

		//---
		// demora proposital
		if(udelay) usleep(udelay);
	}

	// limpar linha
	if(clsline) TERMINAL_CLSLINER();

	// quebrar linha?
	if(newline) printf("\n");

	// ativar cursor novamente
	TERMINAL_CURSOR(1);

	return 0;
}


/*

	printf("\n");
	printf("\n");
	printf("BG ANSI_BPRETO.........: %s%steste             %s\n", ANSI_BPRETO, ANSI_LIGHT, ANSI_RESET);
	printf("BG ANSI_BVERMELHO......: %s%steste             %s\n", ANSI_BVERMELHO, ANSI_LIGHT, ANSI_RESET);
	printf("BG ANSI_BVERDE.........: %s%steste             %s\n", ANSI_BVERDE, ANSI_LIGHT, ANSI_RESET);
	printf("BG ANSI_BLARANJA.......: %s%steste             %s\n", ANSI_BLARANJA, ANSI_LIGHT, ANSI_RESET);
	printf("BG ANSI_BAZUL..........: %s%steste             %s\n", ANSI_BAZUL, ANSI_LIGHT, ANSI_RESET);
	printf("BG ANSI_BROSA..........: %s%steste             %s\n", ANSI_BROSA, ANSI_LIGHT, ANSI_RESET);
	printf("BG ANSI_BCIANO.........: %s%steste             %s\n", ANSI_BCIANO, ANSI_LIGHT, ANSI_RESET);
	printf("BG ANSI_BBRANCO........: %s%steste             %s\n", ANSI_BBRANCO, ANSI_LIGHT, ANSI_RESET);
	printf("BG ANSI_BLIGHT.........: %s%steste             %s\n", ANSI_BLIGHT, ANSI_LIGHT, ANSI_RESET);
	printf("\n");
	printf("FG ANSI_PRETO..........: %steste             %s\n", ANSI_PRETO, ANSI_RESET);
	printf("FG ANSI_VERMELHO.......: %steste             %s\n", ANSI_VERMELHO, ANSI_RESET);
	printf("FG ANSI_VERDE..........: %steste             %s\n", ANSI_VERDE, ANSI_RESET);
	printf("FG ANSI_AMARELO........: %steste             %s\n", ANSI_AMARELO, ANSI_RESET);
	printf("FG ANSI_AZUL...........: %steste             %s\n", ANSI_AZUL, ANSI_RESET);
	printf("FG ANSI_ROSA...........: %steste             %s\n", ANSI_ROSA, ANSI_RESET);
	printf("FG ANSI_CIANO..........: %steste             %s\n", ANSI_CIANO, ANSI_RESET);
	printf("FG ANSI_BRANCO.........: %steste             %s\n", ANSI_BRANCO, ANSI_RESET);
	printf("FG ANSI_LIGHT..........: %steste             %s\n", ANSI_LIGHT, ANSI_RESET);
	printf("\n");
	printf("FG ANSI_PRETOL..........: %steste             %s\n", ANSI_PRETOL, ANSI_RESET);
	printf("FG ANSI_VERMELHOL.......: %steste             %s\n", ANSI_VERMELHOL, ANSI_RESET);
	printf("FG ANSI_VERDEL..........: %steste             %s\n", ANSI_VERDEL, ANSI_RESET);
	printf("FG ANSI_AMARELOL........: %steste             %s\n", ANSI_AMARELOL, ANSI_RESET);
	printf("FG ANSI_AZULL...........: %steste             %s\n", ANSI_AZULL, ANSI_RESET);
	printf("FG ANSI_ROSAL...........: %steste             %s\n", ANSI_ROSAL, ANSI_RESET);
	printf("FG ANSI_CIANOL..........: %steste             %s\n", ANSI_CIANOL, ANSI_RESET);
	printf("FG ANSI_BRANCOL.........: %steste             %s\n", ANSI_BRANCOL, ANSI_RESET);
*/
