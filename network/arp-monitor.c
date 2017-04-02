/*

	arp-monitor

	Monitorar atividade ARP

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <net/if.h>
#include <netpacket/packet.h>


struct std_ethernet {
    unsigned char dest[6];
    unsigned char source[6];
    uint16_t eth_type;
};

struct std_arp {
    uint16_t htype;
    uint16_t ptype;
    unsigned char hlen;
    unsigned char plen;
    uint16_t oper;

    // addresses
    unsigned char sender_ha[6];
    unsigned char sender_pa[4];
    unsigned char target_ha[6];
    unsigned char target_pa[4];

};



#define ARPMONITOR_ETH_HDR_LEN 14
#define ARPMONITOR_BUFF_SIZE 2048
#define ARPMONITOR_ARP_PROTO 0x0806




static void arp_monitor_dump(struct std_ethernet *eth_hdr, void *buffer, int *count){
	struct std_arp *arp_hdr;
	uint16_t htype = ntohs(arp_hdr->htype);
	uint16_t ptype = ntohs(arp_hdr->ptype);
	uint16_t oper = ntohs(arp_hdr->oper);

	// contador de pacotes
	if(*count>0) *count--;

	// pular para posicao do quadro arp
	arp_hdr = (struct std_arp *)(buffer + ARPMONITOR_ETH_HDR_LEN);

	// cabecalho ethernet
	printf("src=%02x:%02x:%02x:%02x:%02x:%02x dst=%02x:%02x:%02x:%02x:%02x:%02x",
		eth_hdr->source[0], eth_hdr->source[1], eth_hdr->source[2],
		eth_hdr->source[3], eth_hdr->source[4], eth_hdr->source[5],
		eth_hdr->dest[0], eth_hdr->dest[1], eth_hdr->dest[2],
		eth_hdr->dest[3], eth_hdr->dest[4], eth_hdr->dest[5]
	);

	switch(ntohs(arp_hdr->oper)){
		case 0x0001:
			printf(" at=request", oper);
			break;
		case 0x0002:
			printf(" at=reply", oper);
			break;
		default:
			printf(" at=oth(%x)", htons(oper));
			break;
	}

	// ARP Sender HA
	printf(" sha=%02x:%02x:%02x:%02x:%02x:%02x",
		arp_hdr->sender_ha[0],arp_hdr->sender_ha[1],arp_hdr->sender_ha[2],
		arp_hdr->sender_ha[3], arp_hdr->sender_ha[4], arp_hdr->sender_ha[5]);
		   
	// ARP Sender PA: 
	printf(" apa=%d.%d.%d.%d", arp_hdr->sender_pa[0],
		arp_hdr->sender_pa[1], arp_hdr->sender_pa[2], arp_hdr->sender_pa[3]);
		   
	// ARP Target HA
	printf(" tha=%02x:%02x:%02x:%02x:%02x:%02x",
		arp_hdr->target_ha[0],arp_hdr->target_ha[1],arp_hdr->target_ha[2],
		arp_hdr->target_ha[3], arp_hdr->target_ha[4], arp_hdr->target_ha[5]);

	// ARP Target PA
	printf(" tpa=%d.%d.%d.%d", arp_hdr->target_pa[0],
		   arp_hdr->target_pa[1], arp_hdr->target_pa[2], arp_hdr->target_pa[3]);

	printf("\n");
}



void help_arp_monitor(void){
	fprintf(stderr,
		"Use: arp-monitor [-a|r] [-i device]\n"
		"  -i device : which ethernet device to use\n"
		"  -c count : limit input packets\n"
		"  -a : only answers (arp request)\n"
		"  -r : only replies (arp reply)\n"
		"  -A : open socket in ARP only mode\n"
		"\n"
	);
	exit(2);
}


int main_arp_monitor(const char *progname, const int argc, const char **argv){
	int sock, err;
	ssize_t recvd_size;
	struct sockaddr_ll s_ll;
	struct std_ethernet *eth_hdr = NULL;
	struct std_arp *arp_hdr = NULL;
	struct ifreq ifr;
	int ifindex;

	void *buffer = NULL;

	char *ifName;
	int filterType = 0;		// filtro de tipo de protocolo arp
	int filterSockARP = 0;		// filtro de tipos de capturas no socket raw
	int count = -1;


// ------------------------------------------------------------------

	int ch;
	int ifOk = 0;
	while ((ch = getopt(argc, (char * const*)argv, "h?i:raAc:")) != EOF) {
		switch(ch) {
		case 'A':
			filterSockARP = 1;
			break;
		case 'a':
			filterType = 1;
			break;
		case 'c':
			count = atoi(optarg);
			break;
			
		case 'r':
			filterType = 2;
			break;
		case 'i':
			ifName = optarg;
			ifOk = 1;
			break;
		case 'h':
		case '?':
		default:
			help_arp_monitor();
		}
	}

	if (!ifOk) help_arp_monitor();

	if(count<1) count = -1;

// ------------------------------------------------------------------

    if( (sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) == -1){
		printf("error=socket\n");
		exit(-1);
    }
	s_ll.sll_family = AF_PACKET;
	s_ll.sll_protocol = htons(ETH_P_ARP); 

	// filtrar interface escolhida
	strncpy(ifr.ifr_name, ifName, IFNAMSIZ);
	if (ioctl(sock, SIOCGIFINDEX, &ifr) == -1) {
		perror("SIOCGIFINDEX");
		printf("error=interface error\n");
		exit(1);
	}
	ifindex = ifr.ifr_ifindex;
	s_ll.sll_ifindex = ifindex;
	
	printf("arp-monitor interface=%s\n", ifName);
	if( (err = bind(sock, (struct sockaddr *)&s_ll, sizeof(s_ll))) == -1){
		printf("error=bind\n");
		exit(6);
	}
	
	buffer = malloc(ARPMONITOR_BUFF_SIZE);
	if(!buffer){
		printf("error=malloc\n");
		exit(6);
	}
	memset(buffer, 0, sizeof(buffer));
	
	while(count!=0){
		if( (recvd_size = recv(sock, buffer, ARPMONITOR_BUFF_SIZE, 0)) == -1){
			printf("error=recv\n");
			free(buffer);
			close(sock);
			exit(3);
		}
		if(recvd_size <= (sizeof(struct std_ethernet) + sizeof(struct std_arp))){
			// printf("Short packet. Packet len: %d\n", recvd_size);
			continue;
		}
		eth_hdr = (struct std_ethernet *)buffer;
		if(ntohs(eth_hdr->eth_type) != ARPMONITOR_ARP_PROTO) continue;

		// pular para posicao do quadro arp
		arp_hdr = (struct std_arp *)(buffer + ARPMONITOR_ETH_HDR_LEN);

		// filtro de tipo
		switch(ntohs(arp_hdr->oper)){
			case 0x0001:
				if(filterType==2) continue;
				arp_monitor_dump(eth_hdr, buffer, &count);
				break;
			case 0x0002:
				if(filterType==1) continue;
				arp_monitor_dump(eth_hdr, buffer, &count);
				break;
			default:
				continue;
		}
		
	}
	free(buffer);
	close(sock);
	return 0;
}

