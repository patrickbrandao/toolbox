
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void help_gethost_ipv6(){
	printf("Use: gethost_ipv6 (hostname)\n");
}

int main_gethost_ipv6 (const char *progname, const int argc, const char **argv){
	struct hostent *he;
	struct in_addr a;

	if (argc != 2){
		fprintf(stderr, "Usage: %s hostname\n", argv[0]);
		return 1;
	}
	char buf[INET6_ADDRSTRLEN];
	bzero(buf, INET6_ADDRSTRLEN);

	he = gethostbyname2(argv[1], AF_INET6);
	if (he){
		while (*he->h_addr_list){
			inet_ntop(AF_INET6, *he->h_addr_list++, buf, sizeof(buf));
			printf("%s\n", buf);
			return 0;
		}
	}else return 1;
	return 2;
}
