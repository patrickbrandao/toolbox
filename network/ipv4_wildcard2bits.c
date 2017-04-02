#include <stdio.h>

/*
	
	Recebe a mascara wildcard (0.0.255.255) e retorna numero de bits (16)

	Exemplo......: ipv4_wildcard2bits 0.7.255.255
		Retorno..: 13

	Exemplo......: ipv4_wildcard2bits 0.0.0.31
		Retorno..: 27

	Exemplo......: ipv4_wildcard2bits 0.0.0.255
		Retorno..: 24

		/30			255.255.255.252			0.0.0.3
		/29			255.255.255.248			0.0.0.7
		/28			255.255.255.240			0.0.0.15
		/27			255.255.255.224			0.0.0.31
		/26			255.255.255.192			0.0.0.63
		/25			255.255.255.128			0.0.0.127
		/24			255.255.255.0			0.0.0.255
		/23			255.255.254.0			0.0.1.255
		/22			255.255.252.0			0.0.3.255
		/21			255.255.248.0			0.0.7.255
		/20			255.255.240.0			0.0.15.255
		/19			255.255.224.0			0.0.31.255
		/18			255.255.192.0			0.0.63.255
		/17			255.255.128.0			0.0.127.255
		/16			255.255.0.0				0.0.255.255
		/15			255.254.0.0				0.1.255.255
		/14			255.252.0.0				0.3.255.255
		/13			255.248.0.0				0.7.255.255
		/12			255.240.0.0				0.15.255.255
		/11			255.224.0.0				0.31.255.255
		/10			255.192.0.0				0.63.255.255
		/9			255.128.0.0				0.127.255.255
		/8			255.0.0.0				0.255.255.255
		/7			254.0.0.0				1.255.255.255
		/6			252.0.0.0				3.255.255.255
		/5			248.0.0.0				7.255.255.255
		/4			240.0.0.0				15.255.255.255
		/3			224.0.0.0				31.255.255.255
		/2			192.0.0.0				63.255.255.255
		/1			128.0.0.0				127.255.255.255

*/
void help_ipv4_wildcard2bits(){
	printf("\n");
	printf("ipv4_wildcard2bits\n");
	printf("Recebe uma mascara wildcard e retorna o numero de bits\n");
	printf("\n");
	printf("Use: ipv4_wildcard2bits (wildcardmask)");
	printf("\n");
	printf("Exemplo: 'ipv4_wildcard2bits 0.7.255.255' retorna 13\n");
	printf("Exemplo: 'ipv4_wildcard2bits 0.0.0.31' retorna 27\n");
	printf("Exemplo: 'ipv4_wildcard2bits 0.0.0.255' retorna 24\n");
	printf("\n");
	exit(1);
}

int main_ipv4_wildcard2bits(const char *progname, const int argc, const char **argv){
//int main(const int argc, const char **argv){
	int j, bits = 0, _end = 0;
	unsigned char nmask[4];
	unsigned int imask[4];

	// ajuda
	if (argc != 2) help_ipv4_wildcard2bits();

	// limpar
	for(j=0;j<4;j++){ nmask[j] = 0; imask[j] = 0; }

	// Obter mascara
	j = sscanf(argv[1],"%d.%d.%d.%d", &imask[0],&imask[1],&imask[2],&imask[3]);
	if(j!=4) return 4;

	// criticar limites
	for (j=0; j<4; ++j)
		if (imask[j]<0 || imask[j]>255)
			return 5;
		//-
	//-

	// mascara obtida. Ler bytes
	_end = 0;
	for (j=0; j<4; ++j){
		if(_end && imask[j]){
			// a mascara acabou mas um numero nao-zero foi informado
			return 6;
		}
		// contar bits
		if(imask[j] == 255){ bits += 8; continue; }
		if(imask[j] == 254){ bits += 7; _end = 1; continue; }
		if(imask[j] == 252){ bits += 6; _end = 1; continue; }
		if(imask[j] == 248){ bits += 5; _end = 1; continue; }
		if(imask[j] == 240){ bits += 4; _end = 1; continue; }
		if(imask[j] == 224){ bits += 3; _end = 1; continue; }
		if(imask[j] == 192){ bits += 2; _end = 1; continue; }
		if(imask[j] == 128){ bits += 1; _end = 1; continue; }
		if(imask[j] == 0){ bits += 0; _end = 1; continue; }
		// bit alienijena na mascara
		return 7;
	}

	// pronto
	printf("%d\n", bits);

	return 0;
}











