

void help_cursor_on(){
	printf("Use: cursor_on\n");
	printf("     Exibe o cursor do terminal caso tenha sido ocultado\n");
}

int main_cursor_on(const char *progname, const int argc, const char** argv){
	TERMINAL_CURSOR(0);
}

