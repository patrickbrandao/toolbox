
#include <stdio.h>

/*
	
	Recebe a mascara decimal (255.255.255.0) e retorna numero de bits (24)

	Exemplo......: ipv4_hmask2prefix 255.0.0.0
		Retorno..: 8

	Exemplo......: ipv4_hmask2prefix 255.255.128.0
		Retorno..: 17

	Exemplo......: ipv4_hmask2prefix 255.255.255.252
		Retorno..: 30

*/
void help_ipv4_hmask2prefix(){
	printf("\n");
	printf("ipv4_hmask2prefix\n");
	printf("Recebe uma mascara de rede e retorna o numero de bits em 1\n");
	printf("\n");
	printf("Use: ipv4_hmask2prefix (mask)");
	printf("\n");
	printf("Exemplo: 'ipv4_hmask2prefix 255.255.0.0' retorna 16\n");
	printf("Exemplo: 'ipv4_hmask2prefix 255.255.255.0' retorna 24\n");
	printf("Exemplo: 'ipv4_hmask2prefix 255.255.255.255' retorna 255\n");
	printf("\n");
	exit(1);
}

int main_ipv4_hmask2prefix(const char *progname, const int argc, const char **argv){
//int main(const int argc, const char **argv){
	int j, bits = 0, _end = 0;
	unsigned char nmask[4];
	unsigned int imask[4];

	// ajuda
	if (argc != 2) help_ipv4_hmask2prefix();

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











