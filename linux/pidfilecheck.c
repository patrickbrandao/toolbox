


void help_pidfilecheck(){
	printf("Use:\n");
	printf("pidfilecheck (pidfile) (process name)\n");
	printf("Stdno:\n");
	printf("\t0 - Sucesso\n");
	printf("Erros:\n");
	printf("\t1 - Parametros insuficientes, informe pidfile e o nome do processo\n");
	printf("\t2 - Arquivo pidfile nao existe\n");
	printf("\t3 - Incapaz de obter conteudo do pidfile\n");
	printf("\t4 - Pid obtido invalido (vazio ou nao-numerico)\n");
	printf("\t5 - Processo nao existe, arquivo /proc/<pid>/cmdline nao existe\n");
	printf("\t6 - Incapaz de abrir arquivo /proc/<pid>/cmdline\n");
	printf("\t7 - Erro de leitura em /proc/<pid>/cmdline\n");
	printf("\t8 - Processo existe, mas nao tem o nome procurado\n");
	printf("\n");
	exit(1);
}


int main_pidfilecheck(const char* progname, const int argc, const char **argv){
	char *pidfile = NULL;		// arquivo com pid
	int pid = 0;				// numero do pid obtido no arquivo
	char *pids = NULL;			// pid numerido convertido para string simples
	char *procname = NULL;		// nome do processo
	char *cmdline = NULL;		// linha de comando lida no /proc/<pid>/cmdline

	int pidfilelen = 0;
	int procnamelen = 0;
	int cmdlinelen = 0;
	
	int fd = 0;
	char buf[128];
	int i = 0, c = 0;
	
	// verificar coerencia
	if(argc > 3 || argc < 3){
		help_pidfilecheck();
		return 1;
	}
	
	// obter parametros
	pidfile = strdup(argv[1]);
	pidfile = trimwhitespace(pidfile);


	procname = strdup(argv[2]);
	procname = trimwhitespace(procname);
	

	pidfilelen = strlen(pidfile);
	procnamelen = strlen(procname);

	
	// faltou informar nome e nome de processo
	if(!pidfilelen || !procnamelen) return 1;
	
	// verificar se o arquivo pid existe
	if(!file_exist(pidfile)) return 2;
	
	// obter conteudo do arquivo pidfile
	fd = open(pidfile, O_RDONLY);
	if(fd == -1) return 3;
	
	// ler conteudo
	bzero(buf, sizeof(buf));
	i = read(fd, buf, sizeof(buf)-1);
	close(fd);
	if(i==-1) return 3;
	buf[i] = '\0';
	pid = atoi( (char *) buf);
	
	// sem pid
	if(!pid) return 4;

//	printf("Conteudo: [%s] PID [%d]\n", buf, pid);

	// verificar se o processo existe
	bzero(buf, sizeof(buf));

	snprintf(buf, sizeof buf, "/proc/%d/cmdline", pid);
//	printf("CMD line patch: %s\n", buf);

	// arquivo cmdline nao existe
	if(!file_exist(buf)) return 5;

	// ler cmdline
	fd = open(buf, O_RDONLY);
	if(fd == -1) return 6;
	bzero(buf, sizeof(buf));
	i = read(fd, buf, sizeof(buf)-1);
	if(i==-1) return 7;
	
	// substituir divisoes anteriores ao tamanho da string
	for(c=0;c<i;c++) if(buf[c]=='\0') buf[c] = ' ';
	buf[i-1] = '\0';

//	printf("CMDLINE: bytes[%d] [%s]\n", i, buf);

	// verificar se o programa desejado se encontra como parte do cmdline
	char *p = NULL;
	p = strstr(buf, procname);
	
	// nao encountrou na string
	if(p==NULL) return 8;

//	printf("strstr: [%s] [%c] [%d]\n", p, p, p);
	
	return 0;

}










