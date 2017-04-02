
// imprime na saida ponto amarelo sem quebra de linha
void help_echo_ydot() {
	printf("Use: echo_ydot\n" );
	printf(" Imprimi ponto amarelo sem quebra de linha\n" );
	exit(1);
}
// principal
int main_echo_ydot(const char *progname, const int argc, const char **argv){
	printf("%s.%s", ANSI_AMARELOL, ANSI_RESET);
	return 0;
}
