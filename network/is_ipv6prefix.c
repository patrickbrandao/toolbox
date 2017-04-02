


void help_is_ipv6prefix(){
	printf("\n");
	printf("is_ipv6prefix\n");
	printf("Verifica se os parametros estao no formato de um endereco ipv6 com prefixo ::/prefix, retorno stdno=0 em caso de correto ou >0 se estiver incorreto\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: is_ipv6prefix (ipv6/prefix) [ipv6/prefix] [ipv6/prefix] [...]\n");
	printf("\n");
	exit(1);
}

int main_is_ipv6prefix(const char* progname, const int argc, const char **argv){
	int i = 0;
    if(argc<2) help_is_ipv6prefix();

	int r = is_ipv6_prefix(argv[1]);

	return r;

}



















