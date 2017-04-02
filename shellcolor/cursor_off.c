

void help_cursor_off(){
	printf("Use: cursor_off\n");
	printf("     Ocultar o cursor do terminal\n");
}

int main_cursor_off(const char *progname, const int argc, const char** argv){
	TERMINAL_CURSOR(0);
}

