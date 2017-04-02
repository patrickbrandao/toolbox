/*
*  C Implementation: ip6calc
*
* Description: a simple tool to calculate IPv6 addresses
*
*
* Author: Konrad Rosenbaum <konrad@silmor.de>, (C) 2009
*
* Copyright: See COPYING file that comes with this distribution
*
*/

#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define IPV6CALC_FMT_SHORT 0
#define IPV6CALC_FMT_DETAIL 1
#define IPV6CALC_FMT_FULL 2

#define IPV6CALC_OUT_NET 1
#define IPV6CALC_OUT_HOST 2
#define IPV6CALC_OUT_MASK 4
#define IPV6CALC_OUT_MAC 8

#define IPV6CALC_OUT_IPM 7
#define IPV6CALC_OUT_IP 3
#define IPV6CALC_OUT_UNTOUCH 0x8000
#define IPV6CALC_OUT_INIT 0x8007

void help_ipv6calc(){

	printf("Usage: ipv6calc [options] address/mask...\n");
	printf("IPv6 calculator\n");
	printf("(c) Konrad Rosenbaum, 2009\n");
	printf("this program is protected under the GNU GPLv3 or at your option any newer\n");
	printf("\n");
	printf("Address parameters:\n");
	printf("  2001:db8::1/64 - address and mask in standard IPv6 notation\n");
	printf("  2001:db8::1 - same address, mask is assumed to be /128\n");
	printf("  /64 - keeps the currently calculated address, but changes the netmask\n");
	printf("  mac:00-11-22-33-44-55 - the mac will be translated into a link local\n");
	printf("    address fe80::211:22ff:fe33:4455/64\n");
	printf("  mac:00-11-22-33-44-55/128 - same translation, but explicit netmask\n");
	printf("  if multiple addresses are given the program attempts to merge them\n");
	printf("\n");
	printf("Output options:\n");
	printf("  -h | --help\n");
	printf("    displays this help text and exit\n");
	printf("  -s | --short\n");
	printf("    print short IPv6 output (eg. 2001:db8::1/128) - this is the default\n");
	printf("  -d | --detail\n");
	printf("    print detailed IPv6 output (eg. 2001:db8:0:0:0:0:0:1/128)\n");
	printf("  -f | --full\n");
	printf("    print full IPv6 output (eg. 2001:0db8:0000:0000:0000:0000:0000:0001)\n");
	printf("  -n | --netid\n");
	printf("    print the network ID\n");
	printf("  -H | --hostid\n");
	printf("    print the host ID\n");
	printf("  -m | --mask\n");
	printf("    print the network mask of the last component\n");
	printf("  -M | --mac\n");
	printf("    attempt to extract a MAC address from the resulting host ID\n");
	printf("\n");
	printf("Examples:\n");
	printf("  %1$s 2001:db8::1/64\n  -> 2001:db8::/64\n");
	printf("  %1$s 2001:db8::1/64 fe80::211:22ff:fe33:4455\n    -> 2001:db8::211:22ff:fe33:4455/128\n");
	printf("  %1$s 2001:db8::1/64 fe80::211:22ff:fe33:4455 /64\n    -> 2001:db8::211:22ff:fe33:4455/64\n");
	printf("  %1$s --netid 2001:db8::211:22ff:fe33:4455/64\n    -> 2001:db8::\n");
	printf("  %1$s --hostid 2001:db8::211:22ff:fe33:4455/64\n    -> ::211:22ff:fe33:4455\n");
	printf("  %1$s --mask 2001:db8::211:22ff:fe33:4455/64\n    -> /64\n");
	printf("  %1$s --netid --hostid --mask 2001:db8::211:22ff:fe33:4455/64\n    -> 2001:db8::211:22ff:fe33:4455/64\n");
	printf("  %1$s 2001:db8::211:22ff:fe33:4455/64\n    -> 2001:db8::211:22ff:fe33:4455/64\n");
	printf("  %1$s --mac 2001:db8::211:22ff:fe33:4455\n    -> MAC=00-11-22-33-44-55\n");
}

int ipv6calc_format=IPV6CALC_FMT_SHORT;
int ipv6calc_outputs=IPV6CALC_OUT_INIT;

#define IPV6CALC_SETOUTPUT(o)	if(ipv6calc_outputs & IPV6CALC_OUT_UNTOUCH) ipv6calc_outputs=0; ipv6calc_outputs |= o

typedef unsigned short ipv6calc_t_ip6addr[8];
ipv6calc_t_ip6addr ipv6calc_caddr={0,0,0,0, 0,0,0,0};
short ipv6calc_cmask=0;

void ipv6calc_printmac(){
	if((ipv6calc_outputs&IPV6CALC_OUT_MAC)==0)return;
	if((ipv6calc_caddr[5]&0xff)==0xff && (ipv6calc_caddr[6]&0xff00)==0xfe00){
		printf("MAC=%02x-%02x-%02x-%02x-%02x-%02x\n",
			(ipv6calc_caddr[4]>>8)^0x02,
			ipv6calc_caddr[4]&0xff,
			ipv6calc_caddr[5]>>8,
			ipv6calc_caddr[6]&0xff,
			ipv6calc_caddr[7]>>8,
			ipv6calc_caddr[7]&0xff
		);
	}else{
		fprintf(stderr,"Result does not contain a MAC address.\n");
		exit(1);
	}
}

void ipv6calc_printdetail(){
	if(ipv6calc_format==IPV6CALC_FMT_FULL)
		printf("%04hx:%04hx:%04hx:%04hx:%04hx:%04hx:%04hx:%04hx", ipv6calc_caddr[0], ipv6calc_caddr[1], ipv6calc_caddr[2], ipv6calc_caddr[3], ipv6calc_caddr[4], ipv6calc_caddr[5], ipv6calc_caddr[6], ipv6calc_caddr[7]);
	else
		printf("%hx:%hx:%hx:%hx:%hx:%hx:%hx:%hx", ipv6calc_caddr[0], ipv6calc_caddr[1], ipv6calc_caddr[2], ipv6calc_caddr[3], ipv6calc_caddr[4], ipv6calc_caddr[5], ipv6calc_caddr[6], ipv6calc_caddr[7]);
	//-
}

void ipv6calc_printshort(){
	int zs=-1,zl=0,mzs=-1,mzl=0,i;
	// shortcut: is it all zero?
	if(!ipv6calc_caddr[0] && !ipv6calc_caddr[1] && !ipv6calc_caddr[2] && !ipv6calc_caddr[3] && !ipv6calc_caddr[4] && !ipv6calc_caddr[5] && !ipv6calc_caddr[6] && !ipv6calc_caddr[7]){
		printf("::");
		return;
	}
	// find longest stretch of zeroes
	for(i=0;i<7;i++){
		if(ipv6calc_caddr[i]){
			// check for maximum
			if(zl>mzl){
				mzl=zl;
				mzs=zs;
			}
			// reset
			zl=0;zs=-1;
		}else{
			// if a zero and previous not, remember pos
			if(!zl)zs=i;
			// increase length
			zl++;
		}
	}

	// check again
	if(zl>mzl){mzl=zl;mzs=zs;}
	
	// print
	if(mzs<0 || mzl<2){
		ipv6calc_printdetail();
		return;
	}
	for(i=0;i<mzs;i++){
		if(i)printf(":");
		printf("%hx",ipv6calc_caddr[i]);
	}
	if(i>=7)return;
	printf("::");
	for(i=mzs+mzl;i<8;i++){
		printf("%hx",ipv6calc_caddr[i]);
		if(i<7)printf(":");
	}
}

void ipv6calc_mergeaddr(ipv6calc_t_ip6addr ip,int mask){
	int i,m;
	/*stage 2: abbrev addrs*/
	m=ipv6calc_cmask;
	for(i=0;i<8;i++){
		if(m>=16)ip[i]=0;else
		if(m<=0)ipv6calc_caddr[i]=0;
		else switch(m){
			case 1:ipv6calc_caddr[i]&=0x8000;ip[i]&=0x7fff;break;
			case 2:ipv6calc_caddr[i]&=0xc000;ip[i]&=0x3fff;break;
			case 3:ipv6calc_caddr[i]&=0xe000;ip[i]&=0x1fff;break;
			case 4:ipv6calc_caddr[i]&=0xf000;ip[i]&=0x0fff;break;
			
			case 5:ipv6calc_caddr[i]&=0xf800;ip[i]&=0x07ff;break;
			case 6:ipv6calc_caddr[i]&=0xfc00;ip[i]&=0x03ff;break;
			case 7:ipv6calc_caddr[i]&=0xfe00;ip[i]&=0x01ff;break;
			case 8:ipv6calc_caddr[i]&=0xff00;ip[i]&=0x00ff;break;
			
			case  9:ipv6calc_caddr[i]&=0xff80;ip[i]&=0x007f;break;
			case 10:ipv6calc_caddr[i]&=0xffc0;ip[i]&=0x003f;break;
			case 11:ipv6calc_caddr[i]&=0xffe0;ip[i]&=0x001f;break;
			case 12:ipv6calc_caddr[i]&=0xfff0;ip[i]&=0x000f;break;
	
			case 13:ipv6calc_caddr[i]&=0xfff8;ip[i]&=0x0007;break;
			case 14:ipv6calc_caddr[i]&=0xfffc;ip[i]&=0x0003;break;
			case 15:ipv6calc_caddr[i]&=0xfffe;ip[i]&=0x0001;break;
		}
		m-=16;
	}
	/*stage 3: merge*/
	for(i=0;i<8;i++)
		ipv6calc_caddr[i]^=ip[i];
	ipv6calc_cmask=mask;
}

void ipv6calc_parseaddr(const char*a){

	int i,j,k,l,mask=128,m,semcnt=0,haddblc=0;
	ipv6calc_t_ip6addr ip={0,0,0,0, 0,0,0,0};
	/*stage 0: is it an IP or a MAC?*/
	if(strncmp("mac:",a,4)==0){

		int i;
		ipv6calc_t_ip6addr ip={0xfe80,0,0,0, 0,0,0,0};
		unsigned char mac[6]={0,0,0, 0,0,0};
		const char*s=a+4;
		/*parse*/
		if(strlen(s)!=17){
			fprintf(stderr,"address %s is not a valid MAC: must be 12 '-' or ':'  separated hex digits\n",a);
			exit(1);
		}
		for(i=0;i<17;i++){
			if((i%3)==2){
				if(s[i]!='-' && s[i]!=':'){
					fprintf(stderr,"address %s is not a valid MAC: invalid separator\n",a);
					exit(1);
				}
				continue;
			}
			mac[i/3]<<=4;
			if(s[i]>='0' && s[i]<='9')mac[i/3]|=s[i]-'0';else
			if(s[i]>='a' && s[i]<='f')mac[i/3]|=s[i]-'a'+10;else
			if(s[i]>='A' && s[i]<='F')mac[i/3]|=s[i]-'A'+10;
			else{
				fprintf(stderr,"address %s is not a valid MAC: it contains non-hex digits\n",a);
				exit(1);
			}
		}
		/*convert*/
		ip[4]=0x200^((mac[0]<<8)|mac[1]);
		ip[5]=(mac[2]<<8)|0xff;
		ip[6]=0xfe00 | mac[3];
		ip[7]=(mac[4]<<8)|mac[5];
		/*merge*/
		ipv6calc_mergeaddr(ip,64);


		return;
	}
	/*stage 1: parse local addr*/
	if(a[0]==':' && a[1]!=':'){
		fprintf(stderr,"address %s is not valid: it must start with a hex digit or ::\n",a);
		exit(1);
	}
	m=-1;
	for(i=j=0;a[i];i++){
		if(j>7){
			fprintf(stderr,"address %s is not valid: more than 8 segments\n",a);
			exit(1);
		}
		if(a[i]=='/')break;
		if(a[i]==':'){
			semcnt++;
			if(!i)continue;
			if(m<0){
				/*its :: */
				if(haddblc){
					fprintf(stderr,"address %s is not valid: only one :: is allowed\n",a);
					exit(1);
				}
				haddblc++;
				l=0;
				for(k=i+1;a[k];k++)if(a[k]==':')l++;
				if((7-l)<j){
					fprintf(stderr,"address %s is not valid: too many :\n",a);
					exit(1);
				}
				j=7-l;
			}else{
				ip[j++]=m;m=-1;
			}
		}else{
			if(m<0)m=0;
			m<<=4;
			if(a[i]>='0'&&a[i]<='9')m|=a[i]-'0';else
			if(a[i]>='a'&&a[i]<='f')m|=a[i]-'a'+10;else
			if(a[i]>='A'&&a[i]<='F')m|=a[i]-'A'+10;
			else{
				fprintf(stderr,"address %s is not valid: %c is not a hex digit\n",a,a[i]);
				exit(1);
			}
			if(m>0xffff){
				fprintf(stderr,"address %s is not valid: max. 4 hex digits per segment\n",a);
				exit(1);
			}
		}
	}
	/*sanity checks*/
	if(i){
		if(semcnt<2 || semcnt>7){
			fprintf(stderr,"address %s is not valid: not enough or too many segments\n",a);
			exit(1);
		}
		if(i>2)
		if(a[i-1]==':'&&a[i-2]!=':'){
			fprintf(stderr,"address %s is not valid: it must not end with a single :\n",a);
			exit(1);
		}
		if(j!=7){
			fprintf(stderr,"address %s is not valid: wrong number of segments\n",a);
			exit(1);
		}
		if(m>=0)ip[j]=m;
	}
	if(a[i]=='/'){
		/*parse mask*/
		char*p;
		i++;
		if(a[i]==0){
			fprintf(stderr,"invalid mask: must contain a decimal number 0<=mask<=128\n");
			exit(1);
		}
		mask=strtol(a+i,&p,10);
		if(*p!=0){
			fprintf(stderr,"invalid mask: not a decimal number\n");
			exit(1);
		}
		if(mask<0 || mask>128){
			fprintf(stderr,"invalid mask: must be between 0 and 128\n");
			exit(1);
		}
	}
	/*stage 1.5: if it is just a mask: skip stage 2*/
	if(a[0]=='/'){
		ipv6calc_cmask=mask;
		return;
	}
	/*stage 2: merge*/
	ipv6calc_mergeaddr(ip,mask);
}

int main_ipv6calc(const char *progname, const int argc, const char**argv){
	int c,optindex=1;

	struct option longopt[]= {
		{"short",0,0,'s'},
		{"detail",0,0,'d'},
		{"full",0,0,'f'},
		{"netid",0,0,'n'},
		{"hostid",0,0,'H'},
		{"mask",0,0,'m'},
		{"mac",0,0,'M'},
		{"help",0,0,'h'},
		{0,0,0,0}
	};


	// parse options
	while(1){
		c=getopt_long(argc, (char * const*)argv,"hsdfnHmM",longopt,&optindex);
		if(c==-1)break;
		switch(c){
			case 's':ipv6calc_format=IPV6CALC_FMT_SHORT;break;
			case 'd':ipv6calc_format=IPV6CALC_FMT_DETAIL;break;
			case 'f':ipv6calc_format=IPV6CALC_FMT_FULL;break;
			case 'n':IPV6CALC_SETOUTPUT(IPV6CALC_OUT_NET);break;
			case 'H':IPV6CALC_SETOUTPUT(IPV6CALC_OUT_HOST);break;
			case 'm':IPV6CALC_SETOUTPUT(IPV6CALC_OUT_MASK);break;
			case 'M':IPV6CALC_SETOUTPUT(IPV6CALC_OUT_MAC);break;
			default:
				fprintf(stderr,"Syntax error in arguments.\n");
				help_ipv6calc();
				return 1;
				break;
			case 'h':
				help_ipv6calc();
				return 0;
				break;
		}
	}

	// parse addresses
	while(optind<argc){
		ipv6calc_parseaddr(argv[optind]);
		optind++;
	}

	// output
	ipv6calc_printmac();
	//ipv6calc_printaddr();

	{
		int m,i;
		ipv6calc_t_ip6addr ip;
		if((ipv6calc_outputs&IPV6CALC_OUT_IPM)!=0){

			// print address
			if(ipv6calc_outputs&IPV6CALC_OUT_IP){
				// null out unwanted parts
				if((ipv6calc_outputs&IPV6CALC_OUT_IP)!=IPV6CALC_OUT_IP){
					memcpy(ip,ipv6calc_caddr,sizeof(ip));
					m=ipv6calc_cmask;
					for(i=0;i<8;i++){
						if(m>=16)ip[i]=0;else
						if(m<=0)ipv6calc_caddr[i]=0;
						else switch(m){
							case 1:ipv6calc_caddr[i]&=0x8000;ip[i]&=0x7fff;break;
							case 2:ipv6calc_caddr[i]&=0xc000;ip[i]&=0x3fff;break;
							case 3:ipv6calc_caddr[i]&=0xe000;ip[i]&=0x1fff;break;
							case 4:ipv6calc_caddr[i]&=0xf000;ip[i]&=0x0fff;break;
							
							case 5:ipv6calc_caddr[i]&=0xf800;ip[i]&=0x07ff;break;
							case 6:ipv6calc_caddr[i]&=0xfc00;ip[i]&=0x03ff;break;
							case 7:ipv6calc_caddr[i]&=0xfe00;ip[i]&=0x01ff;break;
							case 8:ipv6calc_caddr[i]&=0xff00;ip[i]&=0x00ff;break;
							
							case  9:ipv6calc_caddr[i]&=0xff80;ip[i]&=0x007f;break;
							case 10:ipv6calc_caddr[i]&=0xffc0;ip[i]&=0x003f;break;
							case 11:ipv6calc_caddr[i]&=0xffe0;ip[i]&=0x001f;break;
							case 12:ipv6calc_caddr[i]&=0xfff0;ip[i]&=0x000f;break;
					
							case 13:ipv6calc_caddr[i]&=0xfff8;ip[i]&=0x0007;break;
							case 14:ipv6calc_caddr[i]&=0xfffc;ip[i]&=0x0003;break;
							case 15:ipv6calc_caddr[i]&=0xfffe;ip[i]&=0x0001;break;
						}
						m-=16;
					}
					if((ipv6calc_outputs&IPV6CALC_OUT_IP)==IPV6CALC_OUT_HOST)
						memcpy(ipv6calc_caddr,ip,sizeof(ip));
				}
				// actually print
				if(ipv6calc_format==IPV6CALC_FMT_SHORT)
					ipv6calc_printshort();
				else
					ipv6calc_printdetail();
			}
			// print mask
			if(ipv6calc_outputs&IPV6CALC_OUT_MASK)printf("/%hi",ipv6calc_cmask);
			
			// newline
			printf("\n");

		}
	
	}

	return 0;

}




















