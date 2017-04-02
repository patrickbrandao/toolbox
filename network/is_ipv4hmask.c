
/*

	Verificar se e' uma mascara de rede x.x.x.x

*/

void help_is_ipv4hmask(){
	printf("\n");
	printf("is_ipv4hmask\n");
	printf("Verifica o parametro informado e' uma mascara de rede IPv4\n");
	printf("\n");
	printf("Use: ipv4hmask (ipv4mask)\n");
	printf("\n");
	exit(1);
}

int main_is_ipv4hmask(const char *progname, const int argc, const char **argv){
//int main(const int argc, const char **argv){
	int i = 0, r = 0, endbits = 0, bits = 0, last = 0, j;
	int addr[4];

    if(argc!=2) help_is_ipv4hmask();




	// Obter mascara no formato IP
	j = sscanf(argv[1],"%d.%d.%d.%d", &addr[0],&addr[1],&addr[2],&addr[3]);
	if(j!=4) return 1;

	// verificar sanidade dos numeros
	for(i=0;i<4;i++){
		int b = 0;
		if(addr[i] < 0 || addr[i] > 255) return 2;

		switch(addr[i]){
			case 255: b = 8; break;
			case 254: b = 7; break;
			case 252: b = 6; break;
			case 248: b = 5; break;
			case 240: b = 4; break;
			case 224: b = 3; break;
			case 192: b = 2; break;
			case 128: b = 1; break;
			case 0: b = 0; break;
			// numero impossivel na mascara
			default: return 3;
		}
		bits += b;

		// nao pode ter bits depois de terminado um byte menor que 255
		if(b && endbits) return 4;
		if(b!=8) endbits = 1;
	}
	if(bits < 0 || bits > 32) return 5;

	return r;

}


