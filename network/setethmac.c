

 
 void help_setethmac(){

	printf("\n");
	printf("setethmac\n");
	printf("Altera o endereco MAC da interface de rede\n");
	printf("\n");
	printf("Autores: Patrick Brandao <patrickbrandao@gmail.com>, Marcio Araujo <marcioxmarcio@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: setethmac (ethX[.nnn]) (new mac address)\n");
	printf("\n");
	exit(1);

 }

int main_setethmac(const char *progname, const int argc, const char **argv){

	if(argc < 3 || argc > 3) help_setethmac();

    struct ifreq ifr;
    int s;
    char *mac=NULL;
	char *dev=NULL;

	int mac_len = 0;
 
	dev = strdup(argv[1]);
	mac = strdup(argv[2]);

	// validar mac address
	mac_len = strlen(mac);
	if(mac_len != 17){
		printf("invalid mac address format\n");
		return EXIT_FAILURE;
	}

	if(sscanf(mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
		&ifr.ifr_hwaddr.sa_data[0],
		&ifr.ifr_hwaddr.sa_data[1],
		&ifr.ifr_hwaddr.sa_data[2],
		&ifr.ifr_hwaddr.sa_data[3],
		&ifr.ifr_hwaddr.sa_data[4],
		&ifr.ifr_hwaddr.sa_data[5]
	)==6){
	    s = socket(AF_INET, SOCK_DGRAM, 0);
	    assert(s != -1);
	 
	    strcpy(ifr.ifr_name, argv[1]);
	    ifr.ifr_hwaddr.sa_family = ARPHRD_ETHER;
	    assert(ioctl(s, SIOCSIFHWADDR, &ifr) != -1);

	}else{

		// falhou ao ler mac informado
		printf("invalid mac address input\n");
		return EXIT_FAILURE;

	}
 
 
    return EXIT_SUCCESS;

}




