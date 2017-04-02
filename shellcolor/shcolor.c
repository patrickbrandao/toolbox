


int shcolor_yposition = 70;
int shcolor_ystart = 100;

int help_shcolor() {
	fprintf( stderr, "shcolor\n");
	fprintf( stderr, "\tUsage:\n\techo_danger\n\techo_done\n\techo_failure\n\techo_started\n\techo_stopped\n\techo_success\n\techo_skip\n\techo_warnning\n");
}

int shcolor_getprogcode(const char *progbase){
	int pc = 0;
	// printf("Procurando por '%s'\n", progbase);
	if(!strcmp(progbase,"echo_ok")) pc = 0;
	if(!strcmp(progbase,"echo_danger")) pc = 1;
	if(!strcmp(progbase,"echo_done")) pc = 2;
	if(!strcmp(progbase,"echo_failure")) pc = 3;
	if(!strcmp(progbase,"echo_started")) pc = 4;
	if(!strcmp(progbase,"echo_stopped")) pc = 5;
	if(!strcmp(progbase,"echo_success")) pc = 6;
	if(!strcmp(progbase,"echo_skip")) pc = 7;
	if(!strcmp(progbase,"echo_warning")) pc = 8;
	if(!strcmp(progbase,"echo_stop")) pc = 9;
	if(!strcmp(progbase,"echo_unknow")) pc = 10;

	return pc;
}

int main_shcolor(const char *progname, const int argc, const char **argv){

	if(argc>1){
		if(!strcmp(argv[1],"-h") || !strcmp(argv[1],"--help")){
			help_shcolor();
			exit(1);
		}
	}
	int prog = shcolor_getprogcode(progname);

	switch(prog){
		case 0:
			printf("\033[%dD\033[%dC[ %s %sOK %s ]\n",shcolor_ystart,shcolor_yposition , ANSI_VERDEL, ANSI_BOLD,RESET );
			break;
		case 1:
			printf("\033[%dD\033[%dC%s%s%s %sDANGER %s\n",shcolor_ystart,shcolor_yposition ,ANSI_BPRETO, ANSI_AMARELOL,BLINK, ANSI_BOLD,RESET );
			break;
		case 2:
			printf("\033[%dD\033[%dC[ %s%sDONE%s ]\n",shcolor_ystart,shcolor_yposition , ANSI_VERDE, ANSI_BOLD,RESET );
			break;
		case 3:
			printf("\033[%dD\033[%dC%s%s%s %sFAILED %s\n",shcolor_ystart,shcolor_yposition ,ANSI_BVERMELHO, ANSI_BRANCO,BLINK, ANSI_BOLD,RESET );
			break;
		case 4:
			printf("\033[%dD\033[%dC%s%s%s START  %s\n",shcolor_ystart,shcolor_yposition ,ANSI_BVERDE, ANSI_BRANCOL, ANSI_BOLD, ANSI_RESET );
			break;
		case 5:
			printf("\033[%dD\033[%dC%s%s  %sSTOP  %s\n",shcolor_ystart,shcolor_yposition ,ANSI_BVERMELHO, ANSI_BRANCOL, ANSI_BOLD,RESET );
			break;
		case 6:
			printf("\033[%dD\033[%dC[ %s %sOK %s ]\n",shcolor_ystart,shcolor_yposition , ANSI_VERDE, ANSI_BOLD,RESET );
			break;
		case 7:
			printf("\033[%dD\033[%dC[ %s%sSKIP %s]\n",shcolor_ystart,shcolor_yposition , ANSI_AZULL, ANSI_BOLD,RESET );
			break;
		case 8:
			printf("\033[%dD\033[%dC%s%s%s%s  %sWARN %s\n",shcolor_ystart,shcolor_yposition ,ANSI_BPRETO, ANSI_AMARELOL,ANSI_AMARELO,BLINK, ANSI_BOLD,ANSI_RESET );
			break;
		case 9:
			printf("\033[%dD\033[%dC[ %s%sSTOP%s ]\n",shcolor_ystart,shcolor_yposition , ANSI_AMARELOL, ANSI_BOLD,RESET );
			break;
		case 10:
			printf("\033[%dD\033[%dC%s%s UNKNOW %s\n",shcolor_ystart,shcolor_yposition ,ANSI_BBRANCO, ANSI_PRETO, RESET );
			break;

		default:
			help_shcolor();
	}
	return 0;
}