
#include <stdio.h>

/*
	
	CALCULAR O IP DE REDE

	Receber ip no formado ip/bits ou apenas o ip (presume-se /24) e retornar o endereco de rede

	Exemplo......: ipv4_net 192.168.0.0
		Retorno..: 192.168.0.0

	Exemplo......: ipv4_net 192.168.0.9/25
		Retorno..: 192.168.0.0

	Exemplo......: ipv4_net 192.168.0.129/30
		Retorno..: 192.168.0.128

*/
void help_ipv4_net(){
	printf("\n");
	printf("ipv4_net\n");
	printf("Recebe um endereco IPv4 (ip/bits) e retorna o endereco de broadcast\n");
	printf("\n");
	printf("Use: ipv4_net (ipv4[/bits])");
	printf("\n");
	printf("Exemplo: 'ipv4_net 100.70.0.0/10' retorna 100.64.0.0\n");
	printf("Exemplo: 'ipv4_net 192.168.0.0/24' retorna 192.168.0.0\n");
	printf("Exemplo: 'ipv4_net 192.168.0.129/30' retorna 192.168.0.128\n");
	printf("\n");
	exit(1);
}

int main_ipv4_net(const char *progname, const int argc, const char **argv){
//int main(const int argc, const char **argv){
	unsigned long ul_netmask, ul_ipaddr, ul_netaddr, ul_broadcast;
	int i_addr[5], j, bits;
	unsigned char mask[4], bc[4],na[4];

	if (argc != 2) help_ipv4_net();

	// limpar
	for(j=0;j<5;j++){ na[j] = 0; mask[j] = 0; }

	// Obter IP
	j = sscanf(argv[1],"%d.%d.%d.%d/%d", &i_addr[0],&i_addr[1],&i_addr[2],&i_addr[3],&i_addr[4]);
	if(j!=5){
		i_addr[4] = -1;
		j = sscanf(argv[1],"%d.%d.%d.%d", &i_addr[0],&i_addr[1],&i_addr[2],&i_addr[3]);
		if(j!=4) help_ipv4_net();
	}

	// criticar limites
	for (j=0; j<4; ++j)
		if (i_addr[j]<0 || i_addr[j]>255)
			help_ipv4_net();
		//-
	//-

	// mascara padrao /24
	if(i_addr[4] < 0 || i_addr[4] > 32) i_addr[4] = 24;

	// gerar mascara decimal
	ul_netmask = 0;
	j = 0;
	bits = i_addr[4];
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

	// printf("%d.%d.%d.%d/%d\n", i_addr[0], i_addr[1], i_addr[2], i_addr[3], i_addr[4]);
	// printf(" %d.%d.%d.%d\n", mask[0], mask[1], mask[2], mask[3]);

	ul_broadcast = ul_ipaddr | (~ ul_netmask);
	bc[0] = ul_broadcast / 256 / 256 / 256;
	bc[1] = (ul_broadcast / 256 / 256) % 256;
	bc[2] = (ul_broadcast / 256) % 256;
	bc[3] = ul_broadcast % 256;

	ul_netaddr = ul_ipaddr & ul_netmask;
	na[0] = ul_netaddr / 256 / 256 / 256;
	na[1] = (ul_netaddr / 256 / 256) % 256;
	na[2] = (ul_netaddr / 256) % 256;
	na[3] = ul_netaddr % 256;

	// Imprimir apenas broadcast
	printf ("%d.%d.%d.%d\n", na[0], na[1], na[2], na[3]);

	return 0;
}























