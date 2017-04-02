
// imprime na saida ponto vermelho sem quebra de linha
void help_echo_rdot() {
	printf("Use: echo_rdot\n" );
	printf(" Imprimi ponto vermelho sem quebra de linha\n" );
	exit(1);
}
// principal
int main_echo_rdot(const char *progname, const int argc, const char **argv){
	printf("%s.%s", ANSI_VERMELHOL, ANSI_RESET);
	return 0;
}
