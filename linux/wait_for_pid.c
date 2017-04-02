
/*

	Verificar se um processo esta em execucao conferindo a existencia do arquivo de PIDFILE

	Alguns processos iniciam (recebem PID) mas nao criam o pidfile ate que
	todos os check-lists internos sejam cumpridos. Assim, nao podemos
	tomar como certo que um processo subiu so' porque ele esta' em execucao.

	Outra presuncao e' achar que ao enviar um KILL para um processo que ele parou imediatamente.
	Processos podem precisar fechar grandes arquivos e aguardar conexoes de rede serem encerradas
	para entao dar um exit()

	Exemplo:

	wait_for_pid -c -p /var/run/hello-world.pid -t 30 -i 1
		Aguarta 30 segundos (-t 30) ate que o arquivo pidfile (-p /var/run/hello-world.pid) seja criado (-c).
		Verifica se foi criado a cada 1 segundo (-i 1)

	wait_for_pid -r -p /var/run/hello-world.pid -t 21 -i 1
		Aguarta 21 segundos (-t 21) ate que o arquivo pidfile (-p /var/run/hello-world.pid) seja removido (-r).
		Verifica se foi removido a cada 1 segundo (-i 1)

*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

// Ajuda
void help_wait_for_pid(){
	printf("\n");
	printf("wait_for_pid\n");
	printf("Verifica se um arquivo PID foi criado ou removido corretamente,\n");
	printf("\tstdno retorna:\n");
	printf("\t\t0=OK,");
	printf("\t\t1=modo ajuda,");
	printf("\t\t2=nao foi criado,");
	printf("\t\t3=nao foi removido,");
	printf("\t\t4=nao informou o caminho do arquivo\n");
	printf("\t\t5=tempo limite atingido\n");
	printf("\n");
	printf("Autor: Patrick Brandao <patrickbrandao@gmail.com>, todos os direitos reservados\n");
	printf("\n");
	printf("Use: wait_for_pid (-r|-c) -p (pidfile) -t (timeout) -i (interval em dec)\n");
	printf("\n");
	exit(1);	
}


int main_wait_for_pid(const char* progname, const int argc, const char **argv){
//int main(const int argc, const char **argv){

	// tipo: 0=esperar criar, 1=esperar remover
	int type = 0;
	int exist = 0;

	// tempo limite esperando
	int timeout = 0;
	int totaltime = 0; // timeout em decimo de segundos

	// tempo entre verificacoes (decimos de segundos)
	int interval = 10; // 10 = 1 segundo
	int dint = 0;
	int countint = 0; // contador de tempo passado

	// arquivo pidfile
	char *pidfile = NULL;
	char *buf = NULL;


	// Processar argumentos
	char ch;
	while ((ch = getopt(argc, (char * const*)argv, "crp:t:i:h?")) != EOF) {
		switch(ch) {
			// string, arquivo PID
			case 'p':
				pidfile = strdup(optarg);
				break;

			// numero, tempo limite
			case 't':
				timeout = atoi(optarg);
				if(timeout < 1 || timeout > 3600) timeout = 10;
				break;

			// numero, intervalo
			case 'i':
				interval = atoi(optarg);
				if(interval < 1 || interval > 36000) interval = 10;
				break;

			// flags
			case 'c': type = 0; break;
			case 'r': type = 1; break;

			// ajuda
			case 'h':
			case '?':
			default:
				help_wait_for_pid();

		}
	}

	// criticas
	// nada foi informado, mostrar ajuda,  || !pidfile
	if(!interval || !timeout) help_wait_for_pid();

	// erro 4: nao informar o arquivo
	if(!pidfile || !pidfile[0]) return 4;

	// garantir sanidade do intervalo
	dint = interval*100000;

	// calcular tempo maximo a esperar
	totaltime = timeout * 1000000;

	/*
	printf("Type.........: %d\n", type);
	printf("Timeout......: %d\n", timeout);
	printf("Interval.....: %d\n", interval);
	printf("Pidfile......: %s\n", pidfile);
	printf("dInterval....: %d\n", dint);
	printf("Totaltime....: %d\n", totaltime);
	*/

	do{
		exist = 0;

		// verificar se o arquivo existe
		exist = access(pidfile, R_OK) == -1 ? 0 : 1;

		// printf("Verificando -> countint=%d exist=%d type=%d, pidfile=[%s]\n", countint, exist, type, pidfile);

		// se esperamos ele existir e ele existe, pronto!
		if(exist && type==0) return 0;

		// se esperamos ele ser deletado e ele nao existe, pronto!
		if(!exist && type) return 0;

		// contar tempo percorrido
		countint += dint;

		// vontade frustrada... aguardemos

		usleep(dint);

		// limite atingido?
		if(totaltime <= countint) return (type ? 3 : 2);

	} while(1);

	// expirou as tentativas, morrer
	return 0;

}




