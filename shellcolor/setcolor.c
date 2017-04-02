/*

	setcolor: Colorir prompt
	sintax:
	    setcolor cor_texto cor_fundo

*/

void help_setcolor( void ) {
	printf("Use: setcolor (color) (bgcolor)\n");
	exit(1);
}

// principal
int main_setcolor(const char *progname, const int argc, const char **argv){

	// varivel para cor da fonte
	int  txtcolor = 0;

	// variavel para cor de fundo
	int bgcolor = 0;

	// flags especiais de cores de letra
	// -b = negrito
	// -s = sublinhado
	// -p = piscante
	int _text_effect = 0;
	int _light = 0;

	// Processar argumento
	int argn = 1;
	int cl = 0;
	while( argn < argc){

		// recebe argumentos
		if(!strcmp(argv[argn],"blue")) if(cl++) bgcolor = 5; else txtcolor = 5;
		if(!strcmp(argv[argn],"red")) if(cl++) bgcolor = 2; else txtcolor = 2;
		if(!strcmp(argv[argn],"green")) if(cl++) bgcolor = 3; else txtcolor = 3;
		if(!strcmp(argv[argn],"magenta")) if(cl++) bgcolor = 7; else txtcolor = 7;

		if(!strcmp(argv[argn],"cyan")) if(cl++) bgcolor = 7; else txtcolor = 7;
		if(!strcmp(argv[argn],"cian")) if(cl++) bgcolor = 7; else txtcolor = 7;

		if(!strcmp(argv[argn],"pink")) if(cl++) bgcolor = 6; else txtcolor = 6;
		if(!strcmp(argv[argn],"yellow")) if(cl++) bgcolor = 4; else txtcolor = 4;
		if(!strcmp(argv[argn],"white")) if(cl++) bgcolor = 8; else txtcolor = 8;
		if(!strcmp(argv[argn],"light")) if(cl++) bgcolor = 9; else txtcolor = 9;
		if(!strcmp(argv[argn],"black")) if(cl++) bgcolor = 1; else txtcolor = 1;
		if(!strcmp(argv[argn],"gray")) if(cl++) bgcolor = 10; else txtcolor = 10;

		if(!strcmp(argv[argn],"-h") || !strcmp(argv[argn],"--help")){ help_setcolor(); }

		if(!strcmp(argv[argn],"-b")) _text_effect = 1;
		if(!strcmp(argv[argn],"-s")) _text_effect = 2;
		if(!strcmp(argv[argn],"-p")) _text_effect = 3;
		if(!strcmp(argv[argn],"-l")) _light = 1;

		++argn;
	}
    if ( argn != argc ) help_setcolor();

	
	if(txtcolor <= 9 && _light) txtcolor+= 9;
	// printf("txtcolor=[%d] bgcolor=[%bgcolor]\n", txtcolor, bgcolor);
	
	printf("%s%s%s",background_colors[bgcolor], effects[_text_effect], text_colors[txtcolor]);

	return(0);

}



