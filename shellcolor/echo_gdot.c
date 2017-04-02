
// imprime na saida ponto verde sem quebra de linha
void help_echo_gdot() {
	printf("Use: echo_gdot\n" );
	printf(" Imprimi ponto verde sem quebra de linha\n" );
	exit(1);
}
// principal
int main_echo_gdot(const char *progname, const int argc, const char **argv){
	printf("%s.%s", ANSI_VERDEL, ANSI_RESET);
	return 0;
}
