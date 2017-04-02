

void help_ipv6fullread(){
	printf("\n");
	printf("ipv6fullread\n");
	printf("Recebe um endereco IPv6 e imprime endereco no formato completo, aceita varios enderecos de entrada\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: ipv6fullread (ipv6) [ipv6] [ipv6] [...]\n");
	printf("\n");
	exit(1);	
}


int main_ipv6fullread(const char *progname, const int argc, const char **argv){
	int i = 0;

    if(argc<2) help_ipv6fullread();

	ipv6fullread_and_print(argv[1]);

	return 0;
}


