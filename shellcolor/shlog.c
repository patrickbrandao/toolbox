
#define _GNU_SOURCE /* for tm_gmtoff and tm_zone */

#include <stdio.h>
#include <time.h>


void help_shlog(){
	printf("Use: shlog|logit|logit0|logit2|logit3 (string) [string] [string]\n");
	exit( 1 );
}

#define SHLOG_NO_STRNULL(str)	(str ? str : "")
#define SHLOG_NEWLINE()			if(newline) printf("\n")
#define SHLOG_LOGIT(color)		printf ( "%s[%s]%s %s%s%s", ANSI_PRETOL, formatted_gmt, ANSI_RESET, color, SHLOG_NO_STRNULL(str1), ANSI_RESET);SHLOG_NEWLINE()

int main_shlog(const char *progname, const int argc, const char** argv){
//int main(const int argc, const char** argv){
	const char *str1 = NULL; // parametro 1
	const char *str2 = NULL; // parametro 2
	const char *str3 = NULL; // parametro 3
	int i;
	int scount = 1;
	int newline = 1;

	time_t now = time(NULL);
	struct tm gmt = {0};
	int actyear = 0;
	char formatted_gmt [50];

	// sem parametros
	if(argc < 2) help_shlog();

	// processar parametros
	for(i=1; i<argc; i++){
		if(strcmp(argv[i],"-n")==0){ newline = 0; continue; }

		// coletar string
		switch(scount){
			case 1: str1 = argv[i]; scount++; break;
			case 2: str2 = argv[i]; scount++; break;
			case 3: str3 = argv[i]; scount++; break;
		}
	}

	localtime_r(&now, &gmt);
	// actyear = 1900 + gmt.tm_year;
	actyear = gmt.tm_year - 100;

	// obter data-hora completa inversa
	//- sprintf( formatted_gmt, "%04d-%02d-%02d %02d:%02d:%02d", 
	//- 	actyear, gmt.tm_mon+1, gmt.tm_mday,
	//- 	gmt.tm_hour, gmt.tm_min, gmt.tm_sec
	//- );
	sprintf( formatted_gmt, "%02d%02d%02d %02d:%02d:%02d", 
		actyear, gmt.tm_mon+1, gmt.tm_mday,
		gmt.tm_hour, gmt.tm_min, gmt.tm_sec
	);


	// exibir de acordo com o tipo do logit

	// Logit baseado em cores
	// r=vermelho
	if(strcmp(progname,"logitr")==0){ SHLOG_LOGIT(ANSI_VERMELHOL); return 0;}

	// g=green
	if(strcmp(progname,"logitg")==0){ SHLOG_LOGIT(ANSI_VERDEL); return 0;}

	// y=yellow
	if(strcmp(progname,"logity")==0){ SHLOG_LOGIT(ANSI_AMARELOL); return 0;}

	// b=blue
	if(strcmp(progname,"logitb")==0){ SHLOG_LOGIT(ANSI_AZULL); return 0;}

	// p=pink
	if(strcmp(progname,"logitp")==0){ SHLOG_LOGIT(ANSI_ROSAL); return 0;}

	// c=cyan
	if(strcmp(progname,"logitc")==0){ SHLOG_LOGIT(ANSI_CIANOL); return 0;}

	// w=white
	if(strcmp(progname,"logitw")==0){ SHLOG_LOGIT(ANSI_LIGHT); return 0;}

	// a=gray
	if(strcmp(progname,"logita")==0){ SHLOG_LOGIT(ANSI_PRETOL); return 0;}

	// Auxiliar ao conf.sh:

	// 1 parametro: branco
	if(strcmp(progname,"logit0")==0){
		SHLOG_LOGIT(ANSI_LIGHT);
		//printf ( "%s[%s] %s%s%s", ANSI_PRETOL, formatted_gmt, ANSI_LIGHT, SHLOG_NO_STRNULL(str1), ANSI_RESET);
		//SHLOG_NEWLINE();
		return 0;
	}

	// 1 parametros: vermelho
	if(strcmp(progname,"logit1")==0){
		SHLOG_LOGIT(ANSI_VERMELHOL);
		//printf ( "%s[%s] %s%s%s", ANSI_PRETOL, formatted_gmt, ANSI_VERMELHOL, SHLOG_NO_STRNULL(str1), ANSI_RESET);
		//SHLOG_NEWLINE();
		return 0;
	}

	// 2 parametros: verde e rosa
	if(strcmp(progname,"logit2")==0){
		printf ( "%s[%s]%s %s%s%s %s%s", ANSI_PRETOL, formatted_gmt, ANSI_RESET, ANSI_VERDEL, SHLOG_NO_STRNULL(str1), ANSI_CIANOL, SHLOG_NO_STRNULL(str2), ANSI_RESET);
		SHLOG_NEWLINE();
		return 0;
	}

	// 3 parametros: ciano, verde, vermelho
	if(strcmp(progname,"logit3")==0){
		printf ( "%s[%s]%s %s%s%s %s%s %s%s", ANSI_PRETOL, formatted_gmt, ANSI_RESET, ANSI_CIANOL, SHLOG_NO_STRNULL(str1), ANSI_VERDEL, SHLOG_NO_STRNULL(str2), ANSI_ROSAL, SHLOG_NO_STRNULL(str3), ANSI_RESET);
		SHLOG_NEWLINE();
		return 0;
	}

	// 1 parametro padrao: ciano
	// padrao: shlog, logit
	SHLOG_LOGIT(ANSI_CIANOL);

	return 0;

}




