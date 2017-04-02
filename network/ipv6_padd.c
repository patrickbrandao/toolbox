


void help_ipv6_padd(){
	printf("\n");
	printf("ipv6_padd\n");
	printf("Recebe um prefixo IPv6 e o numero que devera ser adicionado ao prefixo, retorna prefixo resultante,\n");
	printf("\tapenas os primeiros 64 bits sao relevantes. O parametro [limit] e' opcional, se informado\n");
	printf("\to calculo nao sera efetuado se (num) acima de [limit]\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: ipv6_padd (ipv6) (num) [limit]\n");
	printf("\n");
	exit(1);
}


int main_ipv6_padd(const char *progname, const int argc, const char **argv){

	long int number = 0;
	long int limit = 0;
	int tmp, len;
	int i = 0;

	// struct ipv6 oficial
	struct in6_addr ipv6addr;

	// representacao string
	char ipv6str[INET6_ADDRSTRLEN];

	// parametros incorretos
    if(argc<3) help_ipv6_padd();

    // obter parametro ipv6
    const char *ipv6 = argv[1];

    // pode acontecer do parametro vir apenas
    // com o prefixo, sem os demais bytes (16 bytes ao todo)
    // vamos 'ajudar' o usuario
    // VAI BUGAR

    // ler ipv6 e jogar em struct
   	ipv6read_prefix(ipv6, &ipv6addr);

   	// numero
   	number = atoi(argv[2]);

   	// tem limite?
   	if(argc == 4) limit = atoi(argv[3]);

    // nao pode violar o limite
    if(limit > 0 && limit < number) return 1;

   	// efetuar operacao
	if(number > 0){
		tmp = number;
		int idx, dif;
		while(tmp > 0){
			idx = 7;

			// quantos numeros podemos incrementar num salto
			dif = tmp - ipv6addr.s6_addr[idx];
			if(dif > 0 && dif < 255){
				ipv6addr.s6_addr[idx] += dif;
				tmp -= dif;
				continue;
			}

			//printf(" A ");print_ipv6full();
			//printf("   %d > idx [%d] = [%d][%d]-[%d]\n", tmp, idx, ipv6addr.s6_addr[idx-2], ipv6addr.s6_addr[idx-1], ipv6addr.s6_addr[idx]);

			// adicionar mais 1
			if(ipv6addr.s6_addr[idx] >= 255){

				while(idx >= 0 && ipv6addr.s6_addr[idx] >= 255){
					// nao da pra aumentar, zerar e aumentar a proxima casa
					ipv6addr.s6_addr[idx] = 0;
					idx--;
					ipv6addr.s6_addr[idx]++;					
				}

			}else{
				ipv6addr.s6_addr[idx]++;
			}

			//printf(" B ");print_ipv6full();
			//printf("   %d > idx [%d] = [%d][%d]-[%d]\n", tmp, idx, ipv6addr.s6_addr[idx-2], ipv6addr.s6_addr[idx-1], ipv6addr.s6_addr[idx]);
			//printf("\n");

			tmp--;
		}

	}

	// Converter para string e informar ao usuario
    inet_ntop(AF_INET6, &(ipv6addr), ipv6str, INET6_ADDRSTRLEN);
    print_ipv6prefix(&ipv6addr);
    //printf("%s\n", ipv6str);

	return 0;

}














