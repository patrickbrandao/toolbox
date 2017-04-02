
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>


// testar se string esta no formato de rede ipv4
int is_ipv4_prefix(const char *str){
	int i, len;
	struct in_addr ipv4addr;
	char addr[INET_ADDRSTRLEN];
	char comp[INET_ADDRSTRLEN];
	int idx1 = 0, idx2 = 0;
	int prefixlen = 0;
	int barcount = 0;

	unsigned long ul_netmask, ul_ipaddr, ul_netaddr, ul_broadcast;
	unsigned char mask[4], bc[4],na[4];
	int i_addr[5];
	int j, bits;

	// string vazia
	if(!str || !str[0]) return 1;

	// tamanho da string
	len=strlen(str);

	// Formatos validos esperados:
	// 0.0.0.0:1 				9 bytes
	// a
	// 255.255.255.255:65535 	21 bytes
	if(len<9 || len > 21) return 2;

	// limpar
	for(j=0;j<5;j++){ na[j] = 0; mask[j] = 0; }

	// limpar a sala
	memset( &(addr), 0, sizeof(addr) );
	memset( &(comp), 0, sizeof(comp) );
	for(i=0; i < len; i++){
		char atch = str[i];

		// nao pode comecar caracter diferente de numero
		if(!i && !isdigit(atch)) return 3;

		// caracter proibidos de acordo com o tipo de requisicao
		if( atch==':' ) return 4;

		// separador de prefixo
		if(atch == '/'){
			barcount++;
			if(barcount > 1) return 6;
			continue;
		}

		// copiar byte para o endereco ou para
		if(barcount){
			// leitura do prefixo
			comp[idx2++] = atch;
		}else{
			// leitura de ip
			addr[idx1++] = atch;
		}
	}

	// parte de endereco e porta lidos, validar
	// 1 - o ip 
	if(!inet_pton(AF_INET, addr, &(ipv4addr))) return 7;

	// 2 - prefixo
	if(!barcount || !idx2) return 8;
	prefixlen = atoi(comp);
	if(prefixlen < 0 || prefixlen > 32) return 9;

	// 3 - verificar se o prefixo informado bate com o prefixo com zeros no host

	// converter string addr para 4 bytes inteiros
	j = sscanf(addr,"%d.%d.%d.%d", &i_addr[0],&i_addr[1],&i_addr[2],&i_addr[3]);
	if(j!=4) return 10;


	// gerar mascara decimal
	ul_netmask = 0;
	j = 0;
	bits = prefixlen;
	while(bits){
		if(bits>=8){ bits-=8; mask[j++] = 255; continue; }
		if(bits==7){ bits-=7; mask[j++] = 254; continue; }
		if(bits==6){ bits-=6; mask[j++] = 252; continue; }
		if(bits==5){ bits-=5; mask[j++] = 248; continue; }
		if(bits==4){ bits-=4; mask[j++] = 240; continue; }
		if(bits==3){ bits-=3; mask[j++] = 224; continue; }
		if(bits==2){ bits-=2; mask[j++] = 192; continue; }
		if(bits==1){ bits-=1; mask[j++] = 128; continue; }
	}
	ul_netmask = mask[3] + 256 * (mask[2] + 256 * (mask[1] + 256 * mask[0]));
	ul_ipaddr = i_addr[3] + 256 * (i_addr[2] + 256 * (i_addr[1] + 256 * i_addr[0]));

	ul_netaddr = ul_ipaddr & ul_netmask;
	na[0] = ul_netaddr / 256 / 256 / 256;
	na[1] = (ul_netaddr / 256 / 256) % 256;
	na[2] = (ul_netaddr / 256) % 256;
	na[3] = ul_netaddr % 256;

	// qualquer diferenca deve resultar em erro
	if(na[0] != i_addr[0]) return 21;
	if(na[1] != i_addr[1]) return 22;
	if(na[2] != i_addr[2]) return 23;
	if(na[3] != i_addr[3]) return 24;

	/*
	// Imprimir apenas broadcast
	printf ("Prefix: %d\n", prefixlen);
	printf ("ul_net: %u\n", ul_netmask);

	printf ("    NA: %d.%d.%d.%d\n", na[0], na[1], na[2], na[3]);
	printf ("  ADDR: %d.%d.%d.%d\n", i_addr[0], i_addr[1], i_addr[2], i_addr[3]);
	*/

	return 0;
}




void help_is_ipv4prefix(){
	printf("\n");
	printf("is_ipv4prefix\n");
	printf("Verifica se o parametro informado e' um prefixo ipv4/bits\n");
	printf("\n");
	printf("Use: is_ipv4prefix (ipv4/prefix)\n");
	printf("\n");
	exit(1);
}

//int main_is_ipv4prefix(const char *progname, const int argc, const char **argv){
int main(const int argc, const char **argv){
	int i = 0;
    if(argc<2) help_is_ipv4prefix();
	int r = is_ipv4_prefix(argv[1]);
	return r;
}






























