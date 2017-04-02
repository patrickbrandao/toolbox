
#include <stdio.h>
#include <stdlib.h>


int main(){

    char *line = NULL;
    size_t size;

    if( getline(&line, &size, stdin) == -1){

        printf("No line\n");

    }else{

        printf("%s\n", line);

    }

    return 0;

}


#include "/tmp/toolbox-libs.h"

#define SHLOADIN_BUF_SIZE 1024


void help_shloading(){
	printf("Use: ./youscript | shloading -l (pre-label) -t (title) -m (total-lines) [-s style]");
	exit(1);
}

/*

--------------------------------------------------------------------------------
Comprimindo baselinux-1.0.txz -----/..... [                                    ]
--------------------------------------------------------------------------------
01234567890123456789
                    x
                     01234567890123456789
                                         x-----/.....
                                          < espaco fixo
                                                     x
                                                      [                        ]
                                                      [ 28.91 %                ]
--------------------------------------------------------------------------------
Label.......: maximo 20
Title.......: maximo 20
Contador....: 11 bytes, 5 para contagem, um /, 5 para o maximo
Barra.......: restante, 1 byte para '[', barra, 1 bytes para ']'
--------------------------------------------------------------------------------

*/

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
	/*
	100 = total
	 pc = count

	pc = 100 * count / total

	*/
}

int main(const int argc, const char **argv){
	int i;
	char label[31]; int llen = 0;
	char title[31]; int tlen = 0;

	// tamanho fixo: label e title
	//char fixbuf[43];
	int fixlen = 0;     // espaco de tamanho fixo, maximo 42

	// espaco da barra
	int barlen = 0;
	char barbuf[81];
	char bar_fill[81];
	char bar_zero[81];

	int style = 0;		// estilo de cores
	int line_count = 0; // numero de linhas recebidas
	int line_total = 0; // total de linhas a processar

	// conteudo do stdin
	char *line = NULL;
	size_t size;
	//char *content;
	//size_t contentSize = 1; // includes NULL

	// espacos em branco no titulo
	bzero(title, 31); bspace(title, 30);
	bzero(label, 31); bspace(label, 30);
	//bzero(fixbuf, 43);
	bzero(barbuf, 81);
	bzero(bar_fill, 81);
	bzero(bar_zero, 81);

	// processar argumentos
	char ch;
	while ((ch = getopt(argc, (char * const*)argv, "l:t:m:s:h?")) != EOF) {
		switch(ch) {
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

			case 'h':
			case '?':
			default:
				help_shloading();
		}
	}
	llen = strlen(label);
	tlen = strlen(title);

	// titulo tem preferencia
	if(tlen>20){
		// retirar label
		llen = 0;
		// nao extrapolar 41 bytes (41 por temos o espaco do label, o divisor e o espaco do titulo)
		if(tlen>41) tlen=41;
	}
	// label nao pode ser menor que 20, salvo se houver espaco nos primeiro 40 bytes
	if(llen>20){
		// estrapolou
		if(llen+tlen > 40){
			// deixar para o label apenas o espaco que sobrou
			llen = 40 - tlen;
		}
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

	// calcular tamanho da barra,
	// considerando que temos em fixlen a quantidade de bytes consumidos e precisamos de 
	// 11 bytes para o contador, 1 bytes para separacao, 2 bytes de chaves '[]''
	barlen = (80 - (fixlen + 1 + 11 + 2));

	// DEBUG
	printf("Title....: [%s] (%d)\n", title, tlen);
	printf("Label....: [%s] (%d)\n", label, llen);
	printf("Style....: (%d)\n", style);
	printf("Style....: (%d)\n", style);
	printf("   barlen: %d\n", barlen);
	printf("TOTAL: %d\n", line_total);

	// Limpar e resetar linha
	TERMINAL_CLSLINER();
	// ocultar cursor
	TERMINAL_CURSOR(0);

	// ler stdin linha-a-linha
	while(getline(&line, &size, stdin) != -1){
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
			if(llen) printf("%s%s%s", ANSI_LIGHT, label, ANSI_RESET);
			// titulo
			if(tlen) printf("%s%s%s", ANSI_CIANOL, title, ANSI_RESET);

			// contadores: -----/.....
			printf("%s%5d/%5d%s ", ANSI_PRETOL, line_count, line_total, ANSI_RESET);

		// calcular porcentagem do total
		fpercent = shloading_percent(line_count, line_total);
		ipercent = (int) fpercent;

		// obter porcentagem de ocupacao da barra
		barcollen = (int) ( ( barlen * ipercent ) / 100 );
		barcolres = barlen - barcollen;

		// criar barra
		bspace(barbuf, 80);
		sprintf(barbuf, " %6.2f %%", fpercent);

		// Desenhar barra de carregamento
			printf("%s[%s", ANSI_LIGHT, ANSI_RESET );

			// imprimir parte carregada
			strncpy(bar_fill, barbuf, 80);
			strncpy(bar_zero, barbuf, 80);

			// limitar as 2 partes para exibi-las corretamente
			// - parte carregada
			if(barcollen) bar_fill[barcollen] = 0;
			if(barcolres){
				// na parte 2, devemos usar o ponteiro para a posicao ocupada
				
			}

			//	char bar_fill[81];
			//	char bar_zero[81];

			// conteudo da barra
			printf("%s%s%s%s", ANSI_BCIANO, ANSI_CIANOL, bar_fill, ANSI_RESET );
			//printf("%.2f / %5d / %10d", fpercent, ipercent, barcollen);

			printf("%s]%s", ANSI_LIGHT, ANSI_RESET );

		// fim do loop
		usleep(20000);


	}

	// Acabaram-se as linhas
	printf("FIM\n");



	return 0;
}

/*


	// ANSI-Cores
	#define		ANSI_RESET		"\033[00m"	//0
	#define		ANSI_VAZIO		""			// NULL

	#define		ANSI_CLRSCR		"\033c"		// limpar a tela

	// FORMATACAO
	#define		ANSI_BOLD		"\033[1m" 	// negrito
	#define		ANSI_SUBT		"\033[4m" 	// sublinhado
	#define		ANSI_BLINK		"\033[5m" 	// piscando


	// TEXT COLOR
	#define 	ANSI_PRETO		"\033[30m"	//1
	#define 	ANSI_VERMELHO	"\033[31m"	//2
	#define 	ANSI_VERDE		"\033[32m"	//3
	#define 	ANSI_AMARELO		"\033[33m"	//4
	#define 	ANSI_AZUL		"\033[34m"	//5
	#define 	ANSI_ROSA		"\033[35m"	//6
	#define 	ANSI_CIANO		"\033[36m"	//7
	#define 	ANSI_BRANCO		"\033[39m"	//8
	#define 	ANSI_LIGHT		"\033[38m"	//9

	// TEXT COLOR LIGHT
	#define 	ANSI_PRETOL		"\033[90m"	//10
	#define 	ANSI_VERMELHOL	"\033[91m"	//11
	#define 	ANSI_VERDEL		"\033[92m"	//12
	#define 	ANSI_AMARELOL	"\033[93m"	//13
	#define 	ANSI_AZULL		"\033[94m"	//14
	#define 	ANSI_ROSAL		"\033[95m"	//15
	#define 	ANSI_CIANOL		"\033[96m"	//16
	#define 	ANSI_BRANCOL		"\033[99m"	//17

	// BACKGROUD
	#define 	ANSI_BPRETO		"\033[40m"	//1
	#define 	ANSI_BVERMELHO	"\033[41m"	//2
	#define 	ANSI_BVERDE		"\033[42m"	//3
	#define 	ANSI_BLARANJA	"\033[43m"	//4
	#define 	ANSI_BAZUL		"\033[44m"	//5
	#define 	ANSI_BROSA		"\033[45m"	//6
	#define 	ANSI_BCIANO		"\033[46m"	//7
	#define 	ANSI_BBRANCO		"\033[47m"	//8
	#define 	ANSI_BLIGHT		"\033[48m"	//9

	// BACKGROUD
	#define 	ANSI_BPRETO		"\033[40m"	//1
	#define 	ANSI_BVERMELHO	"\033[41m"	//2
	#define 	ANSI_BVERDE		"\033[42m"	//3
	#define 	ANSI_BLARANJA	"\033[43m"	//4
	#define 	ANSI_BAZUL		"\033[44m"	//5
	#define 	ANSI_BROSA		"\033[45m"	//6
	#define 	ANSI_BCIANO		"\033[46m"	//7
	#define 	ANSI_BBRANCO		"\033[47m"	//8
	#define 	ANSI_BLIGHT		"\033[48m"	//9

    char *line = NULL;
    size_t size;
    if( getline(&line, &size, stdin) == -1){
        printf("No line\n");
    }else{
        printf("%s\n", line);
    }
*






	//char space80[81];
	//char space40[41];
	//bspace(space80, 80); space80[80] = 0;
	//bspace(space40, 40); space40[40] = 0;

	// processar parametros:
	// titulo (str)
	// tamanho (int)
	// porcentagem (int)


	TERMINAL_CURSOR(0); // ocultar cursor

	// limpar linha
	TERMINAL_CLSLINE();






	TERMINAL_CURSOR(1); // exibir cursor
	fflush(stdout);
}

	/*

	// preparar leitura linha-a-linha da STDIN
	//char buffer[SHLOADIN_BUF_SIZE];
	//content = (char *) malloc(sizeof(char) * SHLOADIN_BUF_SIZE +1);
	//if(content == NULL){ perror("shloading: Failed to allocate content"); exit(1); }
	//bzero(content, SHLOADIN_BUF_SIZE + 1);






	while(fgets(buffer, SHLOADIN_BUF_SIZE, stdin)){

		char *old = content;
		contentSize += strlen(buffer);
		content = realloc(content, contentSize);

		if(content == NULL){
			perror("Failed to reallocate content");
			free(old);
			exit(2);
		}
		strcat(content, buffer);

	}

	if(ferror(stdin)){
		free(content);
		perror("Error reading from stdin.");
		exit(3);
	}
	*/
/*






#define BUF_SIZE 1024
char buffer[BUF_SIZE];
size_t contentSize = 1; // includes NULL
// Preallocate space.  We could just allocate one char here, 
// but that wouldn't be efficient. 
char *content = malloc(sizeof(char) * BUF_SIZE);
if(content == NULL)
{
    perror("Failed to allocate content");
    exit(1);
}
content[0] = '\0'; // make null-terminated
while(fgets(buffer, BUF_SIZE, stdin))
{
    char *old = content;
    contentSize += strlen(buffer);
    content = realloc(content, contentSize);
    if(content == NULL)
    {
        perror("Failed to reallocate content");
        free(old);
        exit(2);
    }
    strcat(content, buffer);
}

if(ferror(stdin))
{
    free(content);
    perror("Error reading from stdin.");
    exit(3);
}


	# Funcoes para exibir carregamento de tarefas longas
	space40="                                        "
	space80="$space40$space40"
	# reset de linha
	_lineclear(){ echoc -n -c white "$space80"; echo -ne '\r'; }
	# imprimir carregamento
	_print_loadin(){
		xtitle="$1"
		xsize="$2"
		xpc="$3"
		if [ "$xpc" -ge "100" ]; then
			_lineclear
			return
		fi
		plen=0
		plen=$(echo -n "$xtitle" | wc -c)
		if [ "$plen" -gt "20" ]; then plen=20; fi
		# * nome do APP
		echoc -n -c white -l "Comprimindo "
		echoc -n -c cyan -l -R $plen "$xtitle"
		plen=$(($plen+12))
		# * separador
		echo -n " "; plen=$(($plen+1))
		# * tamanho do arquivo
		echoc -n -c gray -L 11 "$xsize"; plen=$(($plen+12))
		echo -n " "
		# * abre jaula
		echoc -n -c white "[";
		# 2 bytes da jaula
		plen=$(($plen+2))
		# Quantos bytes restam?
		rlen=$((80-$plen))
		# calcular tamanho da barra
		xleft=0
		xright=0
		if [ "$xpc" -ge "100" ]; then
			# 100%
			xleft=$rlen
			xright=0
		elif [ "$xpc" = "1" ]; then
			# 1%
			xleft=1
			xright=$(($rlen-1))
		else
			tmp=$(($rlen*$xpc))
			tmp=$(($tmp/100))
			if [ "$tmp" = "0" ]; then
				xleft=1
				xright=$(($rlen-1))
			else
				xleft="$tmp"
				xright=$(($rlen-$xleft))
			fi
		fi
		if [ "$xleft" -gt "0" ]; then echoc -b cyan -c cyan -l -n -R "$xleft"  " $xpc %"; fi
		if [ "$xright" -gt "0" ]; then echoc -b blue -c blue -n -R "$xright"    '.........................................................................'; fi
		# * abre jaula
		echoc -n -c white "]"
		echo -ne '\r'
	}

	# loading de descompressao e instalacao do arquivo
	_loading(){
		locLABEL="$1"
		locSIZE="$2"
		locTOTAL="$3"
		xcount=1
		# apagar o cursor
		setterm -cursor off
		# reset de linha
		_lineclear
		# arquivo por arquivo
		while read x; do
			# Calcular porcentagem
			if [ "$xcount" -ge "$locTOTAL" ]; then
				# 100%
				pc=100
				rpc=0
			elif [ "$xcount" = "1" ]; then
				# 1%
				pc=1
			else
				# calcular porcentagem
				pc=$((100*$xcount))
				pc=$(($pc/$locTOTAL))
			fi
			_print_loadin "$locLABEL" "$xcount/$locTOTAL" "$pc"
			xcount=$(($xcount+1))
		done
		# mostrar ultima tela cheia
		_print_loadin "$locLABEL" "$xcount/$locTOTAL" "100"
		# voltar o cursor
		setterm -cursor on
		echo
	}

*/
