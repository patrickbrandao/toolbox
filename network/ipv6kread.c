
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

// exemplo: ipv6kread 28041b40200040009999888877774444

void help_ipv6kread(){
	printf("\n");
	printf("ipv6kread\n");
	printf("Recebe um endereco IPv6 em sequencia hexadecimal direta e imprime endereco no formato resumido\n");
	printf("\n");
	printf("Use: ipv6kread (ipv6)\n");
	printf("\n");
	exit(1);
}

int main_ipv6kread(const char *progname, const int argc, const char **argv){
	struct sockaddr_in6 sa;
	char str[INET6_ADDRSTRLEN];

	int xlen = 0, i, c,j;
	char xstr[INET6_ADDRSTRLEN];

	if(argc<2) help_ipv6kread();

	const char *ipv6str = argv[1];

	
	xlen = strlen(ipv6str);
	if(xlen!=32) return 5;
	
	// zerar novo buffer
	bzero(xstr, INET6_ADDRSTRLEN);
	
	c=0;
	j=0;
	for(i=0;i<32;i++){
		xstr[j++]=ipv6str[i];
		c++;
		if(c==4 && i < 30){
			c = 0;
			xstr[j++]=':';
		}
	}

	// ler de string para strct 128 bits
	inet_pton(AF_INET6, xstr, &(sa.sin6_addr));
	
	// converter struct de 128 bits em notacao string
	inet_ntop(AF_INET6, &(sa.sin6_addr), str, INET6_ADDRSTRLEN);
	printf("%s\n", str);

	return 0;

}

