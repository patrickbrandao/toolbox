
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void help_gethost_ipv4(){
	printf("Use: gethost_ipv4 (hostname)\n");
}

int main_gethost_ipv4 (const char* progname, const int argc, const char **argv){
	struct hostent *he;
	struct in_addr a;

	if (argc != 2){
		help_gethost_ipv4();
		return 1;
	}
	he = gethostbyname (argv[1]);
	if (he){
		while (*he->h_addr_list){
			bcopy(*he->h_addr_list++, (char *) &a, sizeof(a));
			printf("%s\n", inet_ntoa(a));
			return 0;
		}
	}else return 1;
	return 2;
}
