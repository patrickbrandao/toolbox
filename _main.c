/*
	toolbox - main
*/

char *copyright = "Patrick Brandao <patrickbrandao@gmail.com>, Marcio Araujo <marcioxmarcio@gmail.com>. Todos os direitos reservados.";

void help(){
	printf("\n");
	printf("toolbox\n");
	printf("\tCaixa de ferramentas para shell-script TUDO-EM-UM\n");
	printf("Autor: %s\n", copyright);
	printf("\n");
	printf("Use:\n");
	printf("    'toolbox help'          Exibe ajuda principal (esta tela)\n");
	printf("    'toolbox list'          Exibe lista de programas internos\n");
	printf("    'toolbox SOFT help'     Exibe ajuda do sub-programa SOFT\n");
	printf("\n");
	exit(1);
}

// Lista sub-programas
void toolbox_list(){
	int c;
	for(c=0; c < SOFTCOUNT; c++){
		const char *sn = SOFTLIST[c];
		if(!sn || !sn[0]) break;
		printf("%s\n", sn);
	}
}

// Verificar se sub-programa existe
int toolbox_exist(char *sbname){
	int c;
	for(c=0; c < SOFTCOUNT; c++){
		const char *sn = SOFTLIST[c];
		if(!sn || !sn[0]) return 0; // fim da lista
		if(strcmp(sn,sbname)==0) return 1; // encontrou
	}
	return 0; // ? sem fim da lista?
}

// verificar se o nome do sub-programa e' um apelido (e retornar o nome real)
char *toolbox_alias(char *sbname){
	int c;
	char *ret = NULL;
	for(c=0; c < ALIASCOUNT; c++){
		const tb_alias _alias = global_alias_list[c];
		if(!_alias.alias || !_alias.progname) return ret; // fim da lista
		if(strcmp(_alias.alias,sbname)==0){
			// encontrou
			ret = _alias.progname;
			return ret;
		}
	}
	return ret; // ? sem fim da lista?
}

// procurar nome do programa na lista
char *toolbox_getname(char *sbname){
	char *ret = NULL;

	// e' um nome principal?
	if(toolbox_exist(sbname)){
		ret = sbname;
		return ret;
	}

	// e' um alias?
	ret = toolbox_alias(sbname);
	return ret;

}

// Nome do programa invocado pelo usuario
char *USER_CMD_NAME = NULL;

// Nome do sub-programa a ser invocado no codigo (real ou apontado pelo alias)
char *SUB_APP_NAME = NULL;



// MAIN
int main(int argc, char **argv){
	int i;
	// codigo de retorno
	int stdno = 0;
	// modo: 1 = executar, 2 = ajuda
	int mode = 1;
	// gerar copia de argc e argv para o sub-programa?
	int copyarg = 0;

	// obter nome do programa que foi acionado pelo usuario
	USER_CMD_NAME = basename (argv[0]);

	// nome do aplicativo compilado internamente
	// - usar o mesmo que foi digitado, mas temos que resolver isso pelo alias
	SUB_APP_NAME = USER_CMD_NAME;

/*
#ifdef DEBUG
	printf("toolbox ini\n");
	printf("   argc=%d\n", argc);
	for(i=0;i<argc;i++){
		printf("    arg %d = [%s]\n", i, argv[i]);
	}
#endif
*/

	// chamou o proprio toolbox
	if(strcmp("toolbox", USER_CMD_NAME)==0){
		// sem parametros? nao fazer nada (teste de existencia e integridade)
		if(argc < 2) return 0;
		// modo help principal
		if(strcmp("-h",argv[1])==0) help();
		if(strcmp("--help",argv[1])==0) help();
		if(strcmp("help",argv[1])==0) help();
		// modo list?
		if(strcmp("list",argv[1])==0){
			toolbox_list();
			return 0;
		}
		
		// obter nome do APP interno caso tenha sido informado um aliases no arg-zero
		USER_CMD_NAME = argv[1];
		SUB_APP_NAME = toolbox_getname(USER_CMD_NAME);

		if(SUB_APP_NAME){
			// correto
			copyarg = 1;
			// help?
			// o parametro de ajuda deve estar no terceiro parametor
			if(argc > 2 && (strcmp("-h",argv[2])==0) ) mode = 2;

		}else{

			// sub-programa nao encontrado
			return 127;
		}

	}else{

		// nome principal e' o nome do sub-programa
		SUB_APP_NAME = toolbox_getname(USER_CMD_NAME);

		// se nao existe, inutil continuar
		if(!SUB_APP_NAME) return 127;

		// help?
		if(argc > 1 && strcmp("-h",argv[1])==0 ) mode = 2;

	}

	// printf("USER_CMD_NAME: [%s] SUB_APP_NAME: [%s]\n", USER_CMD_NAME, SUB_APP_NAME);

	// modo ajuda do sub-programa?
	if(mode==2){ toolbox_help(SUB_APP_NAME); return 0; }

	// copiar declaracao de argumentos?
	if(copyarg){
		// invocar sub-programa
		stdno = toolbox_exec( (const char*)(SUB_APP_NAME), (const char*)(USER_CMD_NAME), (const int)(argc-1), (const char **)(argv+1) );
	}else{
		// invocar sub-programa
		stdno = toolbox_exec( (const char*)(SUB_APP_NAME), (const char*)USER_CMD_NAME, (const int)(argc), (const char**)argv );
	}


	return stdno;

}














