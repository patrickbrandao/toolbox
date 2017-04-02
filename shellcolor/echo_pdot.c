
// imprime na saida ponto rosa sem quebra de linha
void help_echo_pdot() {
	printf("Use: echo_pdot\n" );
	printf(" Imprimi ponto rosa sem quebra de linha\n" );
	exit(1);
}
// principal
int main_echo_pdot(const char *progname, const int argc, const char **argv){
	printf("%s.%s", ANSI_ROSAL, ANSI_RESET);
	return 0;
}
