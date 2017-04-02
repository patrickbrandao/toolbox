/*
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
*/

void help_ipversion(){
	printf("Use: ipversion (ipv4-or-ipv6)\n");
	printf("Retorna 4 para ipv4, 6 para ipv6\n");
	exit(1);
}


int main_ipversion(const char *progname, const int argc, const char **argv){
	struct addrinfo hint, *res = NULL;
	int ret;
	
	memset(&hint, '\0', sizeof hint);
	
	hint.ai_family = PF_UNSPEC;
	hint.ai_flags = AI_NUMERICHOST;
	
	ret = getaddrinfo(argv[1], NULL, &hint, &res);
	if (ret) {
		printf("unk\n");
	}else{
		if(res->ai_family == AF_INET) {
			printf("4\n");
		} else if (res->ai_family == AF_INET6) {
			printf("6\n");
		} else {
			printf("unk\n");
		}
		freeaddrinfo(res);
	}
	return 0;

}

