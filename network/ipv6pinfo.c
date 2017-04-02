

void help_ipv6pinfo(){
	printf("\n");
	printf("ipv6pinfo\n");
	printf("Recebe um prefixo IPv6 e a quantidade de sub-redes desejadas (prefixos menores)\n");
	printf("\te exibe informacoes do resultado.\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: ipv6pinfo (ipv6-prefix) (subnets)\n");
	printf("\n");
	exit(1);
}

int main_ipv6pinfo(const char *progname, const int argc, const char **argv){

	ipv6prefix six;
	int slen=0;
	int ret = 0;

	if(argc!=3) help_ipv6pinfo();

	// tamanho do sub-prefixo
	slen = atoi(argv[2]);

	// ler prefixo
	ret = ipv6p_read(argv[1], slen, &six);
	if(ret) return ret;

    print_ipv6_prefix(&six);

	return ret;

}
