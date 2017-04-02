
/*

	Verificar se um processo esta em execucao simplesmente consultando se o nome
	do comando se encontra no fim (ou igual) da linha de execucao em CMDLINE

	Exemplo:

	# ps ax
		  419 ?        Ss     0:55 /usr/sbin/syslogd
		  423 ?        Ss     0:00 /usr/sbin/klogd -c 3 -x
		  479 ?        S      0:00 /sbin/udevd --daemon
		  480 ?        S      0:00 /sbin/udevd --daemon
		 3182 ?        Ss     2:57 /usr/sbin/sshd

	# ps_name_exist sshd; echo "Retorno: $?"
	Retorno: 0

	# ps_name_exist udevd; echo "Retorno: $?"
	Retorno: 0

	# ps_name_exist macaco; echo "Retorno: $?"
	Retorno: 1

	(no ultimo exemplo, nao existe processo com o nome 'macaco')

*/

/*
// Ler arquivo e colocar em buffer de no maximo 10.240 bytes
// retornar numero de bytes lidos, ignorar erros
size_t file_to_buffer(char *filepath, char *source){
	FILE *xfp = fopen(filepath, "r");
	if (xfp != NULL) {
		size_t newLen = fread(source, sizeof(char), 1024, xfp);
		if (newLen != 0) source[++newLen] = '\0'; // por seguranca
		fclose(xfp);
		return newLen;
	}
	return 0;
}
*/

// Ajuda
void help_ps_name_exist(){
	printf("\n");
	printf("ps_name_exist\n");
	printf("Verifica se um programa esta em execucao, stdno retorna: 0=rodando, 1=nao esta rodando\n");
	printf("\t0\tRodando (ok)\n");
	printf("\t1\tNao esta rodando\n");
	printf("\t11\tErro de memoria\n");
	printf("\t12\tErro ao abrir /proc\n");
	printf("\t0\tRodando (ok)\n");
	printf("\t0\tRodando (ok)\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: ps_name_exist (process name)\n");
	printf("\n");
	exit(1);	
}


int main_ps_name_exist(const char* progname, const int argc, const char **argv){
	struct dirent *ent;
    char *path = "/proc";
    char *buf;
    char *cmdline;
    char *findps;
	DIR *dir;
    register int len;
    register int found = 0;

    // o argumento precisa ser o nome do processo
    if(argc!=2) help_ps_name_exist();
    len = strlen(argv[1]);
    if(!len) help_ps_name_exist();
    findps = strdup(argv[1]);

    // memoria para trabalho
    buf = calloc(1, 32);
    if(!buf) return 11;

    cmdline = calloc(1, 1024);
    if(!cmdline){ SFREE(buf); return 11;}

    // Abrir diretorio
	if ((dir = opendir (path)) != NULL) {

		// abriu diretorio, listar entradas
		while ((ent = readdir (dir)) != NULL) {
			size_t clen;

			// testar se e' diretorio de processo (numerico)
			if(!ais_numeric(ent->d_name)) continue;

			// limpar
			bzero(buf, 32);
			bzero(cmdline, 1024);

			// construir caminho
			sprintf(buf, "/proc/%s/exe", ent->d_name);

			// verificar se o arquivo existe
			// > nao deu pra ler, ignora
			if(access(buf, R_OK)!=0) continue;

			if ((clen = readlink(buf, cmdline, 1024-1)) != -1){
				char *bn;

				bn = basename(cmdline);

				if(bn && strcmp(bn, findps)==0){

					// achou
					// printf ("%s => %s clen=%d cmdline=%s bn=%s\n", ent->d_name, buf, clen, cmdline, bn);

					closedir(dir);
					SFREE(buf);
					SFREE(cmdline);
					return 0;
				}

				// deu certo
				// 

				// testar


			}
		}
		closedir (dir);

	}else{

		// erro ao abrir o diretorio
		SFREE(buf);
		SFREE(cmdline);
		return 12;

	}

	SFREE(buf);
	SFREE(cmdline);

    return 1;
}







