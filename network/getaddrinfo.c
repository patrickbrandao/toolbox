
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void help_getaddrinfo(){
	printf("Use: getaddrinfo (ip-or-hostname)\n");
}

int main_getaddrinfo (const char *progname, const int argc, const char **argv){
	if (argc < 2) exit (1);

	char *host = strdup(argv[1]);

	struct addrinfo hints, *res;
	int errcode = 0;
	char addrstr[100];
	void *ptr;
	
	memset (&hints, 0, sizeof (hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags |= AI_CANONNAME;

	errcode = getaddrinfo (host, NULL, &hints, &res);
	if (errcode != 0){
		perror ("getaddrinfo");
		return errcode;
	}

	printf ("FQDN=%s\n", host);
	while (res){
		int ipv = res->ai_family == PF_INET6 ? 6 : 4;
		inet_ntop (res->ai_family, res->ai_addr->sa_data, addrstr, 100);
		switch (res->ai_family){
			case AF_INET:
				ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
				break;
			case AF_INET6:
				ptr = &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr;
				break;
		}
		inet_ntop (res->ai_family, ptr, addrstr, 100);
		printf ("IPV%d=%s\n", ipv, addrstr);
		res = res->ai_next;
	}

	return errcode;

}

