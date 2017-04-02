
void help_ipv6read(){
	printf("\n");
	printf("ipv6read\n");
	printf("Recebe um endereco IPv6 e imprime endereco no formato completo, aceita varios enderecos de entrada\n");
	printf("\n");
	printf("Use: ipv6read (ipv6) [ipv6] [ipv6] [...]\n");
	printf("\n");
	exit(1);	
}

void ipv6read(const char *ipv6str){
    struct sockaddr_in6 sa;
    char str[INET6_ADDRSTRLEN];

	// ler de string para strct 128 bits
    inet_pton(AF_INET6, ipv6str, &(sa.sin6_addr));

	// converter struct de 128 bits em notacao string
    inet_ntop(AF_INET6, &(sa.sin6_addr), str, INET6_ADDRSTRLEN);
    printf("%s\n", str);

}

int main_ipv6read(const char* progname, const int argc, const char **argv){
    if(argc<2) help_ipv6read();

	ipv6read(argv[1]);

	return 0;

}


