
// imprime na saida ponto azul claro sem quebra de linha
void help_echo_cdot() {
	printf("Use: echo_cdot\n" );
	printf(" Imprimi ponto azul claro sem quebra de linha\n" );
	exit(1);
}
// principal
int main_echo_cdot(const char *progname, const int argc, const char **argv){
	printf("%s.%s", ANSI_CIANOL, ANSI_RESET);
	return 0;
}
