
#include <stdio.h>

/*
	
	CALCULAR O IP DE BROADCAST

	Receber ip no formado ip/bits ou apenas o ip (presume-se /24) e retornar o endereco de broadcast

	Exemplo......: ipv4_brd 192.168.0.0
		Retorno..: 192.168.0.255

	Exemplo......: ipv4_brd 192.168.0.9/25
		Retorno..: 192.168.0.127

	Exemplo......: ipv4_brd 192.168.0.129/30
		Retorno..: 192.168.0.131

*/
void help_ipv4_brd(){
	printf("\n");
	printf("ipv4_brd\n");
	printf("Recebe um endereco IPv4 (ip/bits) e retorna o endereco de broadcast\n");
	printf("\n");
	printf("Use: ipv4_brd (ipv4[/bits])");
	printf("\n");
	printf("Exemplo: 'ipv4_brd 100.64.0.0/10' retorna 100.127.255.255\n");
	printf("Exemplo: 'ipv4_brd 192.168.0.0/24' retorna 192.168.0.255\n");
	printf("Exemplo: 'ipv4_brd 192.168.0.129/30' retorna 192.168.0.131\n");
	printf("\n");
	exit(1);
}

int main_ipv4_brd(const char *progname, const int argc, const char **argv){
//int main(const int argc, const char **argv){
	unsigned long netmask, ipaddr, netaddr, broadcast;
	int addr[5], j, bits;
	unsigned char mask[4], bc[4],na[4];

	if (argc != 2) help_ipv4_brd();

	// limpar
	for(j=0;j<5;j++){ na[j] = 0; mask[j] = 0; }

	// Obter IP
	j = sscanf(argv[1],"%d.%d.%d.%d/%d", &addr[0],&addr[1],&addr[2],&addr[3],&addr[4]);
	if(j!=5){
		addr[4] = -1;
		j = sscanf(argv[1],"%d.%d.%d.%d", &addr[0],&addr[1],&addr[2],&addr[3]);
		if(j!=4) help_ipv4_brd();
	}

	// criticar limites
	for (j=0; j<4; ++j)
		if (addr[j]<0 || addr[j]>255)
			help_ipv4_brd();
		//-
	//-

	// mascara padrao /24
	if(addr[4] < 0 || addr[4] > 32) addr[4] = 24;

	// gerar mascara decimal
	netmask = 0;
	j = 0;
	bits = addr[4];
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
	netmask = mask[3] + 256 * (mask[2] + 256 * (mask[1] + 256 * mask[0]));
	ipaddr = addr[3] + 256 * (addr[2] + 256 * (addr[1] + 256 * addr[0]));

	// printf("%d.%d.%d.%d/%d\n", addr[0], addr[1], addr[2], addr[3], addr[4]);
	// printf(" %d.%d.%d.%d\n", mask[0], mask[1], mask[2], mask[3]);

	broadcast = ipaddr | (~ netmask);
	bc[0] = broadcast / 256 / 256 / 256;
	bc[1] = (broadcast / 256 / 256) % 256;
	bc[2] = (broadcast / 256) % 256;
	bc[3] = broadcast % 256;

	netaddr = ipaddr & netmask;
	na[0] = netaddr / 256 / 256 / 256;
	na[1] = (netaddr / 256 / 256) % 256;
	na[2] = (netaddr / 256) % 256;
	na[3] = netaddr % 256;

	// Imprimir apenas broadcast
	printf ("%d.%d.%d.%d\n", bc[0], bc[1], bc[2], bc[3]);

	return 0;
}












