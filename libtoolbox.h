/*

	Definicoes, structs e variaveis globais do toolbox
	/
*/

#define DEBUG 1

#ifndef _LIBTOOLBOX_H
#define _LIBTOOLBOX_H


// Item de lista de aliases
typedef struct _tb_alias {
    char *alias;
    char *progname;
} tb_alias;

// ***************************************************************************** CONTROLE DE MEMORIA

#define MY_MALLOC(PTR, MEMSIZE)		PTR = malloc(MEMSIZE+1); if(PTR){ bzero(PTR, MEMSIZE+1); }else exit(1);
#define MY_STRDUP(PTR, STR)			MY_MALLOC(PTR, strlen(STR) * sizeof(char) + 1); strcpy(PTR, STR)
#define SFREE(sp)	if(sp){free(sp); sp=0; }


// ***************************************************************************** EXPRESSAO REGULARES


// testar combinacao ruim
#define REGTEST_QUIT_OK(A, B)	test = test_regex(A, B); if(!test) return 0
#define REGTEST_QUIT_ER(A, B)	test = test_regex(A, B); if(test) return test
#define TOOLBOX_XOR(A, B)		( (A && !B) || (!A && B) )

// retornar:
// 0 - OK
// 1 - nao pegou
// 2 - falha de execucao
int test_regex(const char *exp, const char *str){
	int ret = 0;

	/* aloca espaço para a estrutura do tipo regex_t */
	regex_t reg;

	// Criar objeto para teste
	if (regcomp(&reg , exp, REG_EXTENDED|REG_NOSUB) != 0) {

		// falha de execucao
		ret = 2;

	}else{
		/* tenta casar a ER compilada (&reg) com a entrada (argv[2]) 
		 * se a função regexec retornar 0 casou, caso contrário não */
		if ( (regexec(&reg, str, 0, (regmatch_t *)NULL, 0)) == 0){
			// pegou
			ret = 0;
		}else{
			// nao pegou
			ret = 1;
		}
	}
	return ret;

}







// ***************************************************************************** MANIPULACAO DE STRINGS

#define STR_EXIST_OR_RETURN(STR)	if(!STR || !STR[0]) return



#define ARRDIM(x) (sizeof(x)/sizeof(*(x)))
static const char     *bytes_resume_sizes[]   = { "EiB", "PiB", "TiB", "GiB", "MiB", "KiB", "B" };
static const uint64_t  bytes_resume_exbibytes = 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL;
char *bytes_resume(uint64_t size){
	char     *result = (char *) malloc(sizeof(char) * 20);
	uint64_t  multiplier = bytes_resume_exbibytes;
	int i;
	for (i = 0; i < ARRDIM(bytes_resume_sizes); i++, multiplier /= 1024){   
		if (size < multiplier) continue;
		if (size % multiplier == 0)
			sprintf(result, "%" PRIu64 " %s", size / multiplier, bytes_resume_sizes[i]);
		else
			sprintf(result, "%.1f %s", (float) size / multiplier, bytes_resume_sizes[i]);
		//-
		return result;
	}
	strcpy(result, "0");
	return result;
}

// ler string para uint64_t
uint64_t uint64_t_atoi(const char *strnumber){
	uint64_t ret = 0, gmult = 1;

	int len = 0, i;
	STR_EXIST_OR_RETURN(strnumber) ret;

	len = strlen(strnumber);
	if(!len) return ret;

	for(i=len-1; i >= 0; i--){
		// obter caracter
		char ch = strnumber[i];
		uint64_t tempn = 0;

		// ignorar nao-numerico
		if(ch < 48 || ch > 57) continue;
		tempn = (uint64_t)(ch - 48);
		ret += (gmult * tempn);
		gmult *= 10;
	}
	return ret;
}


// Codificar string em formato hexadecimal
char *hex_encode(unsigned char *inputstring, int *inputlen){
	int i, j;
	char *encode_string = NULL;
	int encoded_len = 0;
	int encoded_idx = 0;

	// nada pra fazer em string vazia
	if(!inputstring) return encode_string;
	// tamanho zero
	if(!*inputlen) return encode_string;

	// Codificar
	encoded_len = *inputlen * 2 + 1;
	encode_string = malloc(encoded_len + 1);
	bzero(encode_string, encoded_len);

	/* processar byte a byte e calcular 2 digitos hexadecimais */
	for(i = 0; i < *inputlen; i++ ){
		unsigned char ch;
		unsigned char enc[2];
		
		enc[0] = 0; enc[1] = 0;

		/* ler byte do texto */
		ch = inputstring[i];
		if(!ch) break;

		/* calcular grandezas relativas a base 16 */
		if(ch) enc[0] = ch / 16;
		if(ch) enc[1] = ch % 16;

		for(j=0;j<2;j++){
			switch(enc[j]){
				case  1: enc[j] = '1'; break;
				case  2: enc[j] = '2'; break;
				case  3: enc[j] = '3'; break;
				case  4: enc[j] = '4'; break;
				case  5: enc[j] = '5'; break;
				case  6: enc[j] = '6'; break;
				case  7: enc[j] = '7'; break;
				case  8: enc[j] = '8'; break;
				case  9: enc[j] = '9'; break;
				case 10: enc[j] = 'A'; break;
				case 11: enc[j] = 'B'; break;
				case 12: enc[j] = 'C'; break;
				case 13: enc[j] = 'D'; break;
				case 14: enc[j] = 'E'; break;
				case 15: enc[j] = 'F'; break;
				default: enc[j] = '0';
			}
			encode_string[encoded_idx++] = enc[j];
		} // for j

	} // for i

	// fechar encode_string
	encode_string[encoded_idx] = 0;

	return encode_string;
}


// obter valor decimal do codigo hexadecimal de 1 caracter
void char_hex_to_dec(unsigned char *chr){
    switch(*chr){
		case '1': *chr = 1; break;
		case '2': *chr = 2; break;
		case '3': *chr = 3; break;
		case '4': *chr = 4; break;
		case '5': *chr = 5; break;
		case '6': *chr = 6; break;
		case '7': *chr = 7; break;
		case '8': *chr = 8; break;
		case '9': *chr = 9; break;
		case 'a': case 'A': *chr = 10; break;
		case 'b': case 'B': *chr = 11; break;
		case 'c': case 'C': *chr = 12; break;
		case 'd': case 'D': *chr = 13; break;
		case 'e': case 'E': *chr = 14; break;
		case 'f': case 'F': *chr = 15; break;
		default: *chr = 0;
    }
}



unsigned char *hex_decode(char *encodec_string){
	int i, j;
	unsigned char *output_string = NULL;
	int output_len = 0;
	int encoded_len = 0;
	int decoded_len = 0;
	int decode_idx = 0;

	// nada pra fazer
	if(!encodec_string) return output_string;
	if(!encodec_string[0]) return output_string;

	encoded_len = strlen(encodec_string);
	if(encoded_len < 2) return output_string;

	// tamanho da string decodificada e' metade da original
	decoded_len = encoded_len / 2;
	encoded_len = decoded_len * 2;
	decoded_len++;
	output_string = (unsigned char*)malloc(decoded_len+1);
	bzero(output_string, decoded_len+1);

	// analisar de 2 em 2
	j = 0;
	for(i=0; i < encoded_len; i+= 2){
		char c1, c2;
		char cr;

		c1 = encodec_string[i];
		c2 = encodec_string[i+1];

		// converter para decimal
		char_hex_to_dec(&c1);
		char_hex_to_dec(&c2);

		// recuperar byte original
		cr = (c1*16) + c2;

		// catalogar no resultado
		output_string[decode_idx++] = cr;
	}
	return output_string;
}

// inverter uma string
void str_reverse(char *str){
	char *buf = NULL;
	register int len, i;
	register int total;

	// nada a fazer
	STR_EXIST_OR_RETURN(str);

	// tamanho da string
	len = strlen(str);

	// nao da pra inverter 1 byte ne!
	if(len <= 2) return;

	// alocar
	total = (len+1) * (sizeof(char)) + 1;
	MY_MALLOC(buf, total);

	// inverter
	for(i=0; i < len; i++) buf[i] = str[len-i-1];

	// copiar de volta pro original
	for(i=0; i < len; i++) str[i] = buf[i];
}


// preencher ponteiro com espacos
void bspace(char *ptr, int size){
	register int i;
	for(i=0; i<size;i++) ptr[i] = ' ';
}


// retirar todos os caracteres nao-numericos
void str_only_numbers(char *str){
	register int len = 0, k = 0, i = 0;
	// nada a fazer
	STR_EXIST_OR_RETURN(str);
	len = strlen(str);
	for(i = 0; i < len; i++){
		if(isdigit(str[i]))
			str[k++] = str[i];
		//-
	}
	// apagar o resto
	for(i = k; i < len; i++) str[i] = 0;
}



// depurar espaco de memoria
void str_mem_debug(char *ptr, int size){
	register int i, j=0;
	printf("STRING DEBUG, LEN (%d) SIZE (%d):\n", strlen(ptr), size);
	for(i=0; i< size; i++){
		printf("[%c] %h", ptr[i] ? ptr[i] : '?', ptr[i]);
		if(j++==40){ printf("\n"); j = 0; }
	}
	printf("\n\n");
}



// formatar numero, entrada: 1234 saida 1.234
char *str_number_format(const char *input){
	register int alocsize = 0, inputlen = 0;
	register int newlen = 0, k, m, n;
	char *ret = NULL, *workspace = NULL;

	// nada a fazer
	if(!input || !input[0]) return ret;

	// tamanho da entrada
	inputlen = strlen(input);
	if(inputlen < 4){
		// nada a fazer, duplicar e retornar
		MY_STRDUP(ret, input);
		return ret;
	}

	// tamanho da string para trabalho
	alocsize = (inputlen * sizeof(char)) + (inputlen > 3 ? inputlen / 3 : inputlen) + 3;

	// alocar espaco para retorno e gerar copia local
	MY_MALLOC(ret, alocsize);
	MY_MALLOC(workspace, alocsize);
	strcpy(ret, input);

	// apenas numeros sao permitidos
	str_only_numbers(ret);

	newlen = strlen(ret);
	if(!newlen++) sprintf(ret, "0");

	// inverter ordem
	str_reverse(ret);

	// temos apenas os numeros invertidos, escreve-los com pontos
	k = 0;
	n = 1;
	for(m = 0; m < newlen; m++){
		workspace[k++] = ret[m];
		if(n++ == 3){ n = 1; if( m+2 < newlen) workspace[k++] = '.'; }
	}
	// inverter novamente
	str_reverse(workspace);
	return workspace;
}

// converter para minusculas
void str_to_lower(char *str){
	char *_str;
	register int i, len;
	register int k;
	STR_EXIST_OR_RETURN(str);
	len = strlen(str);
	if(len)
		for(i=0; i < len; i++)
			str[i] = tolower(str[i]);
	//-
}


// trim
char *trimwhitespace(char *str){
	char *end;
	// Trim leading space
	while(isspace(*str) || *str == '\t') str++;
	if(*str == 0) return str;
	// Trim trailing space
	end = str + strlen(str) - 1;
	while(end > str && (isspace(*end) || *end=='\n' ) ) end--;
	// Write new null terminator
	*(end+1) = 0;
	return str;
}



// comparar semelhanca de bytes entre primeira string
// e segunda string
// a primeira string nao pode ser contrariada dentro da segunda string
// precisa estar contida no inicio da primeira para ter retorno >=
// retorna o numero de bytes iguais nas duas strings
// csense testa com (1) ou sem(0) suporte case-sensitive
// A primeira string e' uma ocorrencia real, enquando que a segunda
// string e' uma palavra apelido
// parametro igno
/*
----------------------------------------------- normal
p real:		addr
apelido:	a
result:		1

p real:		ip
apelido:	ipv
result:		0

p real:		ipv
apelido:	ip
result:		2

p real:		ping
apelido:	pool
result:		1

p real:		p
apelido:	pool
result:		0

p real:		pin
apelido:	pinoia
result:		3
----------------------------------------------- anormal
p real:		addr
apelido:    adr
result:     2

*/
int strmathcount(const char *name, const char *nick, const int csense){
	register int k;
	register int nicklen, namelen;
	int ret = 0;
	// obter tamanhos
	namelen = strlen(name);
	nicklen = strlen(nick);

//	printf("Entrada:\n\tstring1: %s\n\tstring2: %s\n", name, nick);

	// nao e' apelido, tem letras a mais
	if(nicklen>namelen){
		ret = 0;
	}else{
		// comparar bytes
		for(k=0; k < nicklen; k++){
			// comparacao simples case-sensitive
			if(csense && name[k]==nick[k]){ ret++; continue; }
			// comparacao sem case senstivie
			if(tolower(name[k]) == tolower(nick[k])){ ret++; continue; }

			// nao pegou, incompativeis
			// palavras tomaram rumo diferentes, desconsiderar
			ret = 0;
			break;
		}
	}
	//printf(" > Retorno: %d\n", ret);
	return ret;
}


// comprar strings sem case-sensitive
int string_comp_nocase_like(const char *word, const char *strtotest){
	int ret = 0;

	char *_word = NULL;
	char *_strtotest = NULL;

	// duplicar
	_word = strdup(word);
	if(!_word) return 0;

	_strtotest = strdup(strtotest);
	if(!_strtotest) return 0;

	// converter para minusculas
	str_to_lower(_word);
	str_to_lower(_strtotest);

	// printf("  Compare '%s' com '%s'\n", _word, _strtotest);

	// comparar similaridade
    ret = strmathcount(_word, _strtotest, 0);

	// cleanup
	free(_word);
	free(_strtotest);

	return ret;
}


// converter para maiusculas
void str_to_upper(char *str){
	char *_str;
	register int i, len;
	register int k;
	STR_EXIST_OR_RETURN(str);
	len = strlen(str);
	if(len)
		for(i=0; i < len; i++)
			str[i] = toupper(str[i]);
	//-
}


// colocar espacos a esquerda do texto
char *str_pad_left(const char *input, int space){
	char *ret = NULL;
	register int i, len, offset = 0, idx = 0;

	// espaco necessario (space + 1)
	MY_MALLOC(ret, space + 1);

	// preencher com espacos que vamos utilizar
	bspace(ret, space);

	// usuario nao passou nada
	// facil retornar apenas espacos
	if(!input || !input[0]) return ret;

	// tamanho do texto
	len = strlen(input);

	offset = space - len;
	if(offset < 0) offset = 0;

	// copiar por cima dos espacos, respeitando limites
	for(i=offset; i < space; i++) ret[i] = input[idx++];

	return ret;
}

// colocar espacos a direita do texto
char *str_pad_right(const char *input, int space){
	char *ret = NULL;
	register int i, len;

	// espaco necessario (space + 1)
	MY_MALLOC(ret, space + 1);

	// preencher com espacos que vamos utilizar
	bspace(ret, space);

	// usuario nao passou nada
	// facil retornar apenas espacos
	if(!input || !input[0]) return ret;

	// copiar texto dentro do limite
	len = strlen(input);
	if(len > space) len = space;
	for(i = 0; i < len; i++) ret[i] = input[i];

	// str_mem_debug(ret, space);
	return ret;
}


// comprar strings sem case-sensitive
int string_comp_nocase(const char *word, const char *strtotest){
	int ret = 0;

	char *_word = NULL;
	char *_strtotest = NULL;

	// duplicar
	_word = strdup(word);
	if(!_word) return 0;

	_strtotest = strdup(strtotest);
	if(!_strtotest) return 0;

	// converter para minusculas
	str_to_lower(_word);
	str_to_lower(_strtotest);

	// printf("  Compare '%s' com '%s'\n", _word, _strtotest);

	// transformar as duas em minusculas
	if(strcmp(_word, _strtotest)==0) ret = 1;

	// cleanup
	free(_word);
	free(_strtotest);

	return ret;
}


// testar se string esta no formato FQDN (com ponto)
int is_fqdn(const char *str){
	register int i;
	int test = 0;
	int len = strlen(str);
	int bcount = 0, dcount = 0;
	int have_dot = 0;

	// impossivel ter um nome menor que 3 bytes: x.y
	if(len < 3) return 8;
	// impossivel ter um mac maior que 256 bytes
	if(len > 254) return 9;

// analise de caracteres
	for(i=0;i<len;i++){
		char ch = str[i];
		char bf = 0;

		// caracter anterior
		if(i) bf = str[i-1];

		// converter para minusculo
		ch = tolower(ch);

		// tem ponto?
		if(ch=='.') have_dot++;

		// caracter proibido
		if(ch != '.' && ch != '-' && !isalnum(ch)) return 7;

		// nao pode comecar com ponto ou traco
		if(!i && (ch=='.'||ch=='-')) return 6;

		// nao pode terminar com traco
		// (pode terminar com ponto, FQDN de dns termina com ponto)
		if(i+1==len && ch=='-') return 5;

		// nao pode ter ponto ou traco duplo
		if( (ch=='.' || ch=='-') && bf == ch ) return 4;

	}

	// sem ponto, nome simples nao pode ser FQDN
	if(!have_dot) return 3;

	// passou por todas as verificacoes de erros
	return 0;
}


// testar se string esta no formato de nome simples de host
int is_dnshost(const char *str){
	register int i;
	int test = 0;
	int len = strlen(str);
	int bcount = 0, dcount = 0;
	int have_dot = 0;

	// impossivel ter um nome menor que 1 bytes: x
	if(len < 1) return 8;
	// impossivel ter um mac maior que 256 bytes
	if(len > 254) return 9;

// analise de caracteres
	for(i=0;i<len;i++){
		char ch = str[i];
		char bf = 0;

		// caracter anterior
		if(i) bf = str[i-1];

		// converter para minusculo
		ch = tolower(ch);

		// tem ponto?
		if(ch=='.') have_dot++;

		// caracter proibido
		if(ch != '.' && ch != '-' && !isalnum(ch)) return 7;

		// nao pode comecar com ponto ou traco
		if(!i && (ch=='.'||ch=='-')) return 6;

		// nao pode terminar com traco
		// (pode terminar com ponto, FQDN de dns termina com ponto)
		if(i+1==len && ch=='-') return 5;

		// nao pode ter ponto ou traco duplo
		if( (ch=='.' || ch=='-') && bf == ch ) return 4;

	}

	// nao pode ter ponto
	if(have_dot) return 3;

	// passou por todas as verificacoes de erros
	return 0;
}

// testar se string esta no formato numerico inteiro
int is_integer(const char *str){
	char atch;
	char lastch;
	char nextch;
	register int i, j;

	int len;

	// string vazia
	if(!str || !str[0]) return 1;

	// tamanho da string
	len=strlen(str);
	if(!len) return 2;


	// Formatos validos esperados:
	// 1
	// 123456
	// 193839
	// 00001222
	// 12.3
	// 1239.04

	// nao valido:
	// 123.
	// .192

	// Loop byte a byte

	// loop
	for(i=0;i<len;i++){
		atch = str[i];
		lastch = i ? str[i-1] : 0;

		if(isdigit(atch)) continue;

		// caracter invalido
		return 4;

	} // for i

	// tudo correto
	return 0;
}


// a string deve possuir so numeros
int only_numbers(const char *str){
	int _len, i;
	if(!str || !str[0]) return 1;
	_len = strlen(str);
	for(i=0; i < _len; i++) if(!isdigit(str[i])) return 2;
	return 0;
}


// testar se string esta no formato ipv4
// porta na mesma declaracao
int is_ipv4(const char *str){
	struct in_addr ipv4addr;
	if(!inet_pton(AF_INET, str, &(ipv4addr))) return 1;
	return 0;
}



// testar se string esta no formato ipv4
// se is_prefix for 1, sera verificado se a mascara foi informada em numero de bits
// se have_port for 1, sera verificado se a porta foi informada, mas nao e' possivel ter o prefixo e a
// porta na mesma declaracao
int is_ipv4_port(const char *str){
	int i, len;
	struct in_addr ipv4addr;
	char addr[INET_ADDRSTRLEN];
	char comp[INET_ADDRSTRLEN];
	int idx1 = 0, idx2 = 0;
	int port = 0;
	int dotcount = 0;
	int comacount = 0;

	// string vazia
	if(!str || !str[0]) return 1;

	// tamanho da string
	len=strlen(str);

	// Formatos validos esperados:
	// 0.0.0.0:1 				9 bytes
	// a
	// 255.255.255.255:65535 	21 bytes
	if(len<9 || len > 21) return 2;

	// limpar a sala
	memset( &(addr), 0, sizeof(addr) );
	memset( &(comp), 0, sizeof(comp) );
	for(i=0; i < len; i++){
		char atch = str[i];

		// nao pode comecar caracter diferente de numero
		if(!i && !isdigit(atch)) return 3;

		// caracter proibidos de acordo com o tipo de requisicao
		if( atch=='/' ) return 4;

		// ponto
		if(atch == '.'){
			dotcount++;
			if(dotcount > 3) return 5;
		}
		// separador de porta
		if(atch == ':'){
			comacount++;
			if(comacount > 1) return 6;
			continue;
		}

		// copiar byte para o endereco ou para
		if(comacount){
			// leitura do ip
			comp[idx2++] = atch;
		}else{
			// leitura de porta
			addr[idx1++] = atch;
		}
	}

	// parte de endereco e porta lidos, validar
	// 1 - o ip 
	if(!inet_pton(AF_INET, addr, &(ipv4addr))) return 7;

	// 2 - porta
	port = atoi(comp);
	if(port < 1 || port > 65535) return 8;

	return 0;
}



// testar se string esta no formato de rede ipv4
int is_ipv4_prefix(const char *str){
	int i, len;
	struct in_addr ipv4addr;
	char addr[INET_ADDRSTRLEN];
	char comp[INET_ADDRSTRLEN];
	int idx1 = 0, idx2 = 0;
	int prefixlen = 0;
	int barcount = 0;

	unsigned long ul_netmask, ul_ipaddr, ul_netaddr, ul_broadcast;
	unsigned char mask[4], bc[4],na[4];
	int i_addr[5];
	int j, bits;

	// string vazia
	if(!str || !str[0]) return 1;

	// tamanho da string
	len=strlen(str);

	// Formatos validos esperados:
	// 0.0.0.0:1 				9 bytes
	// a
	// 255.255.255.255:65535 	21 bytes
	if(len<9 || len > 21) return 2;

	// limpar
	for(j=0;j<5;j++){ na[j] = 0; mask[j] = 0; }

	// limpar a sala
	memset( &(addr), 0, sizeof(addr) );
	memset( &(comp), 0, sizeof(comp) );
	for(i=0; i < len; i++){
		char atch = str[i];

		// nao pode comecar caracter diferente de numero
		if(!i && !isdigit(atch)) return 3;

		// caracter proibidos de acordo com o tipo de requisicao
		if( atch==':' ) return 4;

		// separador de prefixo
		if(atch == '/'){
			barcount++;
			if(barcount > 1) return 6;
			continue;
		}

		// copiar byte para o endereco ou para
		if(barcount){
			// leitura do prefixo
			comp[idx2++] = atch;
		}else{
			// leitura de ip
			addr[idx1++] = atch;
		}
	}

	// parte de endereco e porta lidos, validar
	// 1 - o ip 
	if(!inet_pton(AF_INET, addr, &(ipv4addr))) return 7;

	// 2 - prefixo
	if(!barcount || !idx2) return 8;
	prefixlen = atoi(comp);
	if(prefixlen < 0 || prefixlen > 32) return 9;

	// 3 - verificar se o prefixo informado bate com o prefixo com zeros no host

	// converter string addr para 4 bytes inteiros
	j = sscanf(addr,"%d.%d.%d.%d", &i_addr[0],&i_addr[1],&i_addr[2],&i_addr[3]);
	if(j!=4) return 10;


	// gerar mascara decimal
	ul_netmask = 0;
	j = 0;
	bits = prefixlen;
	while(bits){
		if(bits>=8){ bits-=8; mask[j++] = 255; continue; }
		if(bits==7){ bits-=7; mask[j++] = 254; continue; }
		if(bits==6){ bits-=6; mask[j++] = 252; continue; }
		if(bits==5){ bits-=5; mask[j++] = 248; continue; }
		if(bits==4){ bits-=4; mask[j++] = 240; continue; }
		if(bits==3){ bits-=3; mask[j++] = 224; continue; }
		if(bits==2){ bits-=2; mask[j++] = 192; continue; }
		if(bits==1){ bits-=1; mask[j++] = 128; continue; }
	}
	ul_netmask = mask[3] + 256 * (mask[2] + 256 * (mask[1] + 256 * mask[0]));
	ul_ipaddr = i_addr[3] + 256 * (i_addr[2] + 256 * (i_addr[1] + 256 * i_addr[0]));

	ul_netaddr = ul_ipaddr & ul_netmask;
	na[0] = ul_netaddr / 256 / 256 / 256;
	na[1] = (ul_netaddr / 256 / 256) % 256;
	na[2] = (ul_netaddr / 256) % 256;
	na[3] = ul_netaddr % 256;

	// qualquer diferenca deve resultar em erro
	if(na[0] != i_addr[0]) return 21;
	if(na[1] != i_addr[1]) return 22;
	if(na[2] != i_addr[2]) return 23;
	if(na[3] != i_addr[3]) return 24;

	/*
	// Imprimir apenas broadcast
	printf ("Prefix: %d\n", prefixlen);
	printf ("ul_net: %u\n", ul_netmask);

	printf ("    NA: %d.%d.%d.%d\n", na[0], na[1], na[2], na[3]);
	printf ("  ADDR: %d.%d.%d.%d\n", i_addr[0], i_addr[1], i_addr[2], i_addr[3]);
	*/

	return 0;
}


// testar se string esta no formato ipv6
int is_ipv6(const char *str){
	struct in6_addr ipv6addr;
	if(!inet_pton(AF_INET6, str, &(ipv6addr))) return 1;
	return 0;
}



// testar se string esta no formato de rede ipv6 com porta
int is_ipv6_port(const char *str){
	int i, len;
	struct in6_addr ipv6addr;
	char addr[INET6_ADDRSTRLEN + 9];
	char comp[INET6_ADDRSTRLEN + 9];
	int idx1 = 0, idx2 = 0;
	int port = 0;
	int commacount = 0;

	// controle de "[ ipv6 ]:xx" em relacao ao '[' e ']'
	int _status = 0; // 0=nao aberto, 1=aberto, 2=fechado

	// string vazia
	if(!str || !str[0]) return 1;

	// tamanho da string
	len=strlen(str);

	// Formatos validos esperados:
	// [::]:0 												6 bytes
	// a
	// [1111:2222:3333:4444:aaaa:bbbb:cccc:dddd]:65535 		47 bytes
	if(len<6 || len > 47) return 2;

	// limpar a sala
	memset( &(addr), 0, sizeof(addr) );
	memset( &(comp), 0, sizeof(comp) );
	for(i=0; i < len; i++){
		char atch = str[i];

		// printf("ch=%c status=%d\n", atch, _status);

		// abrindo
		if(atch == '['){
			if(_status!=0) return 3;
			_status = 1; // abrindo
			continue;
		}
		// fechando
		if(atch == ']'){
			if(_status!=1) return 4;
			_status = 2; // fechando
			continue;
		}

		// encontramos a porta
		if(atch == ':'){
			if(_status==2){
				commacount++;
				if(commacount > 1) return 5;
				// nao coletar esse byte
				continue;
			}
		}

		// copiar byte para o endereco ou para
		if(commacount){
			// estamos lendo a porta
			comp[idx2++] = atch;
		}else{
			// leitura de ipv6
			// problema: nao estamos dentro do '[' .. ']'
			if(_status!=1) return 7;
			addr[idx1++] = atch;
		}
	}
	// printf("ADDR: '%s' COMP: '%s'\n", addr, comp);

	// parte de endereco e porta lidos, validar
	// 1 - o ip 
	if(!inet_pton(AF_INET6, addr, &(ipv6addr))) return 8;

	// 2 - porta
	if(!commacount || !idx2) return 9;
	port = atoi(comp);
	if(port < 1 || port > 65535) return 10;

	return 0;
}


// testar se string esta no formato de rede ipv6
int is_ipv6_prefix(const char *str){
	int i, len;
	struct in6_addr ipv6addr;
	char addr[INET6_ADDRSTRLEN + 4];
	char comp[INET6_ADDRSTRLEN + 4];
	int idx1 = 0, idx2 = 0;
	int prefix = 0;
	int barcount = 0;

	// string vazia
	if(!str || !str[0]) return 1;

	// tamanho da string
	len=strlen(str);

	// Formatos validos esperados:
	// ::/0 												4 bytes
	// a
	// 1111:2222:3333:4444:aaaa:bbbb:cccc:dddd/128 			43 bytes
	if(len<4 || len > 43) return 2;

	// limpar a sala
	memset( &(addr), 0, sizeof(addr) );
	memset( &(comp), 0, sizeof(comp) );
	for(i=0; i < len; i++){
		char atch = str[i];

		// encontramos o prefixo
		if(atch == '/'){
			barcount++;
			if(barcount > 1) return 3;
			continue;
		}

		// copiar byte para o endereco ou para
		if(barcount){
			// estamos lendo a prefixo
			comp[idx2++] = atch;
		}else{
			// leitura de ipv6
			addr[idx1++] = atch;
		}
	}
	// printf("ADDR: '%s' COMP: '%s'\n", addr, comp);

	// parte de endereco e prefixo lidos, validar
	// 1 - o ip 
	if(!inet_pton(AF_INET6, addr, &(ipv6addr))) return 5;

	// 2 - prefixo
	if(!barcount || !idx2) return 6;
	prefix = atoi(comp);

	// printf("Prefixo: %d\n", prefix);

	if(prefix < 0 || prefix > 128) return 7;

	return 0;
}


// testar se string esta no formato ipv4
// porta na mesma declaracao
int is_mac(const char *str){
	register int i;
	int test = 0;
	int len = strlen(str);
	int bcount = 0, dcount = 0;

	// impossivel ter um mac menor que 12 bytes: 0:1:2:3:4:5
	if(len < 6) return 8;
	// impossivel ter um mac maior que 17 bytes: 00_11_22_33_44_55
	if(len > 17) return 9;

// analise de caracteres
	for(i=0;i<len;i++){
		char ch = str[i];
		// e' digito?
		int isd = isxdigit(ch);
		// e' divisor?
		int iss = ch=='.' || ch == '-' || ch == ':';

		if(isd) bcount++;
		if(iss) dcount++;

		if(isd || iss) continue;

		// caracter do mal, vaza
		return 6;
	}
	// numero de bytes lidos nao pode ser menor que 6, exemplo: 0:1:2:a:b:c
	// numero de bytes lidos nao pode ser menor que 12
	if(bcount < 6) return 5;
	if(bcount > 12) return 4;

	// nao podem haver mais que 5 divisores
	if(dcount > 5) return 11;

// combinacoes aceitas como 100% corretas

	// HEX puro
	if(bcount==12 && dcount == 0) return 0;

	// LINUX: 00:11:22:aa:bb:cc
	REGTEST_QUIT_OK("^([0-9A-Fa-f]{2}:){5}([0-9A-Fa-f]{2})$", str);

	// WIN: 00-11-22-aa-bb-cc
	REGTEST_QUIT_OK("^([0-9A-Fa-f]{2}-){5}([0-9A-Fa-f]{2})$", str);

	// CISCO: 001122-aabbcc
	REGTEST_QUIT_OK("^([0-9A-Fa-f]{2}){3}-([0-9A-Fa-f]{2}){3}$", str);

	// Mikrotik: 0:0:a:c:ff:af
	REGTEST_QUIT_OK("^([0-9A-Fa-f]{1,2}:){5}([0-9A-Fa-f]{1,2})$", str);

	return 7;

}


// testar se string esta no formato numerico inteiro
int is_numeric(const char *str){
	char atch;
	char lastch;
	char nextch;
	register int i, j;

	int len;

	// string vazia
	if(!str || !str[0]) return 1;

	// tamanho da string
	len=strlen(str);
	if(!len) return 2;


	// Formatos validos esperados:
	// 1
	// 123456
	// 193839
	// 00001222
	// 12.3
	// 1239.04

	// nao valido:
	// 123.
	// .192

	// Loop byte a byte

	// controles
	int dotcount = 0;

	// loop
	for(i=0;i<len;i++){
		atch = str[i];
		lastch = i ? str[i-1] : 0;

		if(atch=='.'){ dotcount++; continue;}

		if(isdigit(atch)) continue;

		// caracter invalido
		return 4;

	} // for i

	// pontos demais
	if(dotcount>1) return 5;

	// apenas 1 ponto
	if(len==1 && dotcount) return 6;

	// tudo correto
	return 0;
}


// testar se e' um numero
int ais_numeric(const char * s){
	if (s == NULL || *s == '\0' || isspace(*s)) return 0;
	char * p;
	strtod (s, &p);
	return *p == '\0';
}



// ********************************************************************************************************* Formatacao de rede



// ler string e interpretar ipv4 a partir dela
#define INET_PTON_NG_ZERO4(a, b)	{ a[0]=0; a[1]=0; a[2]=0; a[3]=0; b=0; }
#define INET_PTON_NG_COLET(_readed, _read, _idx) if(_readed && _idx < 4){ int total; total = atoi(_read); nums[idx] = total; INET_PTON_NG_ZERO4(_read, _readed); }
static int inet_pton_ng(const char *src){
	int nums[4];
	register int i, r, idx, j, readed;
	register char c;
	char *mystr;
	char read[4];

	for(i=0;i<4;i++) nums[i] = 0;
	
	c = *src;
	j = 15;
	idx = 0;
	INET_PTON_NG_ZERO4(read, readed);

	while(j-- && idx < 4){
		if(c=='.'){
			// se ha coleca de numeros, contabilizar no slot de idx
			INET_PTON_NG_COLET(readed, read, idx);
			c = *++src;
			idx++;
			continue;
		}
		if(isdigit(c)){
			if(readed<3) read[readed++] = c;
			c = *++src;
			continue;
		}
		// caracter desconhecido
		break;
	}
	
	// ultima sequencia
	INET_PTON_NG_COLET(readed, read, idx);

	// converter para decimal
	nums[1] = nums[1] << 8;
	nums[2] = nums[2] << 16;
	nums[3] = nums[3] << 24;

	r = nums[0] + nums[1] + nums[2] + nums[3];
	return r;
}

// ler string ipv6 para um struct, mas pagar os 64 bits de host
void ipv6read_prefix(const char *ipv6str_input, struct in6_addr * s_ipv6){
    int i;

	// ler de string para strct 128 bits
	inet_pton(AF_INET6, ipv6str_input, s_ipv6);

    // zerar todas as casas apos primeiros 64 bits
    for(i=8; i < 16; i++) s_ipv6->s6_addr[i] = 0;

}

// imprimir apenas prefixo do ipv6
void print_ipv6prefix(struct in6_addr * s_ipv6){
	printf("%02x%02x:%02x%02x:%02x%02x:%02x%02x\n",
		s_ipv6->s6_addr[0],
		s_ipv6->s6_addr[1], //-
		s_ipv6->s6_addr[2],
		s_ipv6->s6_addr[3], //-
		s_ipv6->s6_addr[4],
		s_ipv6->s6_addr[5], //-
		s_ipv6->s6_addr[6],
		s_ipv6->s6_addr[7]  //-
	);	
}


// ler string ipv6, instalar na struct ipv6 e postar o endereco ipv6 sem abreviar zeros
void ipv6fullread_and_print(const char *ipv6str){
    struct sockaddr_in6 sa;

	// ler de string para strct 128 bits
    inet_pton(AF_INET6, ipv6str, &(sa.sin6_addr));

	// converter struct de 128 bits em notacao hexadecimal completa
	printf("%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x\n",
			sa.sin6_addr.s6_addr[0],
			sa.sin6_addr.s6_addr[1],
			sa.sin6_addr.s6_addr[2],
			sa.sin6_addr.s6_addr[3],
			sa.sin6_addr.s6_addr[4],
			sa.sin6_addr.s6_addr[5],
			sa.sin6_addr.s6_addr[6],
			sa.sin6_addr.s6_addr[7],
			sa.sin6_addr.s6_addr[8],
			sa.sin6_addr.s6_addr[9],
			sa.sin6_addr.s6_addr[10],
			sa.sin6_addr.s6_addr[11],
			sa.sin6_addr.s6_addr[12],
			sa.sin6_addr.s6_addr[13],
			sa.sin6_addr.s6_addr[14],
			sa.sin6_addr.s6_addr[15]
		);	
}









// IPv6
// Gestao de Pools e prefixos IPv6 para ND e DHCP-PD
//

// struct para armazenar prefixo
typedef struct ipv6prefix_s {
	struct in6_addr network;	// endereco da rede
	unsigned int plen;			// tamanho do prefixo
	unsigned int slen;			// tamanho das subnets
	int32_t scount;				// numero de subnets
	int32_t sbits;				// numero de bits a variar
} ipv6prefix;

int ipv6p_prefix_read(const char *prefix, ipv6prefix *px);
int ipv6p_read(const char *prefix, const int slen, ipv6prefix *px);
void print_in6_addr(struct in6_addr ipv6ia);
void print_in6_addr_prefix(struct in6_addr ipv6ia);
void print_ipv6_prefix(ipv6prefix *px);


// Ler prefixo: endereco ipv6 e numero de bits
// retorna:
// 0 = ok
// N = onde N e' o numero do erro
//	1 = nao informou o prefixo
//	2 = mascara (tamanho do prefixo) invalida sintaticamente
//	3 = caracter invalido no prefixo
//	4 = nao e' prefixo, muito pequeno
//	5 = nao e' prefixo, sem mascara, precisa ser de /10 a /63
//	6 = mascara violou padrao
//	7 = erro no parse do endereco ipv6
int ipv6p_prefix_read(const char *prefix, ipv6prefix *px){
	int len;			// tamanho da string entrada
	int plen=0;			// tamanho do endereco do prefixo (parte ipv6)
	int psize = 0;		// numero de bits do prefixo
	char ipv6str[INET6_ADDRSTRLEN];
	int i;

	// zerar
	memset(px, 0, sizeof(ipv6prefix));
	memset(&ipv6str, 0, INET6_ADDRSTRLEN);

	if(!prefix || !prefix[0]) return 1;
	len = strlen(prefix);
	if(len < 4) return 4;

	// copiar ipv6 ate a mascara
	for(i=0; i<len; i++){
		if(prefix[i]=='/') break;
		ipv6str[i] = prefix[i];
		plen++;
	}
	if(plen == len) return 5;

	psize = atoi( &(prefix[plen]) + 1);
	if(psize < 10 || psize > 63) return 5;
	printf("Ler [%s] IPv6=[%s] Psize=%d\n", prefix, ipv6str, psize);

	// fazer conversao para 128 bits
	if(!inet_pton(AF_INET6, ipv6str, &(px->network))) return 7;
	px->plen = psize;

	return 0;
}

// Caulo de potencia
// falta

// carregar struct com prefixo e tamanho do prefixo delegado
// retorna: 0=ok, 10=incoerencia no tamanho do sub-prefixo
int ipv6p_read(const char *prefix, const int slen, ipv6prefix *px){
	register int ret = 0, j, bits;
	// converter string para formato ipv6
	ret = ipv6p_prefix_read(prefix, px);
	if(ret) return ret;

	// zerar 64bits eui64
	//for(j=8;j<16;j++) px->network.s6_addr[j] = 0;

	// zerar bits que nao pertencam ao prefixo
	// percorrer a cada 8 bits e comecar
	// a zerar os bits onde atingirmos um restante menor igual a 8
	bits = px->plen;
	j = 0;
	while(bits > 0 || j < 16){
		if(bits >= 8){
			// ignorar esse byte, o prefixo
			// cobre ele
			bits-=8;

		}else if(bits > 0){
			// temos que fazer uma operacao
			// 'and' na casa atual com o numero
			// de bits restantes no prefixo
			int oldbyte = px->network.s6_addr[j];
			int newbyte = oldbyte;

			// calcular numero decimal que representa os bits
			// que faltam para gerar um AND com o byte do IPv6
			int calc = 0;
			int rbits = (8-bits); // numero de bits em zeros
			while(rbits-->0) calc = (calc<<1) + 1; // calcular binario em 1 nos espacos em zero
			calc = 255 - calc; // inverter

			newbyte &= calc;

			//printf("> Operando casa %d, byte=%d (%02x), bits-restantes=%d bits-dec=%d (%02x) resultado-and=%d (%02x)",
			//	j, oldbyte, oldbyte, bits, calc, calc, newbyte, newbyte
			//);

			px->network.s6_addr[j] = newbyte;

			// acabou
			bits = 0;
		}else{
			// casa nao coberta pelo prefixo, zerar
			//printf(" -> zerar casa %d\n", j);
			px->network.s6_addr[j] = 0;
		}
		j++;
	}

	// sub-prefixos
	px->slen = slen;
	if(px->plen > px->slen) return 10;
	px->sbits = px->slen - px->plen;

	// total:
	px->scount = -1;

	// calcular apenas numeros realmente utilizaveis!
	// 4 bilhoes bastam
	if(px->sbits <= 32 && px->sbits > 0){
		int32_t sbits = (px->sbits);
		int32_t total = 1;
		int32_t count;
		//printf("Calcular numero de subnets para %d -> %d\n", sbits, total);
		for(count=0; count < sbits; count++){
		//while(sbits >= 0){
			//printf(" %u -> %u\n", sbits, total);
			total = (total*2);
			//printf("    %u => %u\n", count, total);
		}
		px->scount = (total);
		//printf("Total cauculado: %u\n", px->scount);
	}
	return ret;
}

//--------------------------------------------- generico:

// imprimir struct de ipv6 completo
void print_in6_addr(struct in6_addr ipv6ia){
	printf("%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x\n",
		ipv6ia.s6_addr[0], ipv6ia.s6_addr[1], ipv6ia.s6_addr[2], ipv6ia.s6_addr[3],
		ipv6ia.s6_addr[4], ipv6ia.s6_addr[5], ipv6ia.s6_addr[6], ipv6ia.s6_addr[7],
		ipv6ia.s6_addr[8], ipv6ia.s6_addr[9], ipv6ia.s6_addr[10], ipv6ia.s6_addr[11],
		ipv6ia.s6_addr[12], ipv6ia.s6_addr[13], ipv6ia.s6_addr[14], ipv6ia.s6_addr[15]
	);
}
// imprimir struct de ipv6 apenas PREFIXO 64 bits
void print_in6_addr_prefix(struct in6_addr ipv6ia){
	printf("%02x%02x:%02x%02x:%02x%02x:%02x%02x\n",
		ipv6ia.s6_addr[0], ipv6ia.s6_addr[1], ipv6ia.s6_addr[2], ipv6ia.s6_addr[3],
		ipv6ia.s6_addr[4], ipv6ia.s6_addr[5], ipv6ia.s6_addr[6], ipv6ia.s6_addr[7]
	);
}

// imprimir struct ipv6prefix
void print_ipv6_prefix(ipv6prefix *px){
	printf("IPv6 Prefix\n");
	printf("\tCompleto.........: "); print_in6_addr(px->network);
	printf("\tPrefixo..........: ");

	printf("%02x%02x:%02x%02x:%02x%02x:%02x%02x::/%d\n",
		px->network.s6_addr[0], px->network.s6_addr[1], px->network.s6_addr[2], px->network.s6_addr[3],
		px->network.s6_addr[4], px->network.s6_addr[5], px->network.s6_addr[6], px->network.s6_addr[7],
		px->plen
	);

	printf("\tBits prefixo.....: %d\n", px->plen);
	printf("\tBits sub-prefix..: %d\n", px->slen);
	printf("\tBits sub-nets....: %d\n", px->sbits);
	printf("\tTotal sub-nets...: %u\n", px->scount);

}




// ***************************************************************************** SISTEMA DE ARQUIVOS

// verificar se o arquivo existe
int file_exist(const char* filename){
	struct stat buffer;
	int exist = stat(filename,&buffer);
	if(exist == 0) return 1; else return 0;
}




// ***************************************************************************** FUNCOES e CORES DE TERMINAL

// exibir/ocultar cursos de digitacao
#define TERMINAL_CURSOR(status)		printf("\e[?25%c", status ? 'h' : 'l')
#define TERMINAL_RETURN()			printf("\r")
#define TERMINAL_CLSLINE()			TERMINAL_RETURN(); {int term_i; for(term_i=0;term_i<80;term_i++) printf(" ");}
#define TERMINAL_CLSLINER()			TERMINAL_CLSLINE(); TERMINAL_RETURN()

/*
	\033[x;yH     posiciona o cursor na linha x, coluna y
	\033[xA       move o cursor x linhas para cima
	\033[xB       move o cursor x linhas para baixo
	\033[yC       move o cursor y colunas para a direita
	\033[yD       move o cursor y colunas para a esquerda
*/


// ANSI-Cores
#define		ANSI_RESET		"\033[00m"	//0
#define		ANSI_VAZIO		""			// NULL

#define		ANSI_CLRSCR		"\033c"		// limpar a tela

// FORMATACAO
#define		ANSI_BOLD		"\033[1m" 	// negrito
#define		ANSI_SUBT		"\033[4m" 	// sublinhado
#define		ANSI_BLINK		"\033[5m" 	// piscando


// TEXT COLOR
#define 	ANSI_PRETO		"\033[30m"	//1
#define 	ANSI_VERMELHO	"\033[31m"	//2
#define 	ANSI_VERDE		"\033[32m"	//3
#define 	ANSI_AMARELO		"\033[33m"	//4
#define 	ANSI_AZUL		"\033[34m"	//5
#define 	ANSI_ROSA		"\033[35m"	//6
#define 	ANSI_CIANO		"\033[36m"	//7
#define 	ANSI_BRANCO		"\033[39m"	//8
#define 	ANSI_LIGHT		"\033[38m"	//9

// TEXT COLOR LIGHT
#define 	ANSI_PRETOL		"\033[90m"	//10
#define 	ANSI_VERMELHOL	"\033[91m"	//11
#define 	ANSI_VERDEL		"\033[92m"	//12
#define 	ANSI_AMARELOL	"\033[93m"	//13
#define 	ANSI_AZULL		"\033[94m"	//14
#define 	ANSI_ROSAL		"\033[95m"	//15
#define 	ANSI_CIANOL		"\033[96m"	//16
#define 	ANSI_BRANCOL		"\033[99m"	//17

// BACKGROUD
#define 	ANSI_BPRETO		"\033[40m"	//1
#define 	ANSI_BVERMELHO	"\033[41m"	//2
#define 	ANSI_BVERDE		"\033[42m"	//3
#define 	ANSI_BLARANJA	"\033[43m"	//4
#define 	ANSI_BAZUL		"\033[44m"	//5
#define 	ANSI_BROSA		"\033[45m"	//6
#define 	ANSI_BCIANO		"\033[46m"	//7
#define 	ANSI_BBRANCO		"\033[47m"	//8
#define 	ANSI_BLIGHT		"\033[48m"	//9

// BACKGROUD
#define 	ANSI_BPRETO		"\033[40m"	//1
#define 	ANSI_BVERMELHO	"\033[41m"	//2
#define 	ANSI_BVERDE		"\033[42m"	//3
#define 	ANSI_BLARANJA	"\033[43m"	//4
#define 	ANSI_BAZUL		"\033[44m"	//5
#define 	ANSI_BROSA		"\033[45m"	//6
#define 	ANSI_BCIANO		"\033[46m"	//7
#define 	ANSI_BBRANCO		"\033[47m"	//8
#define 	ANSI_BLIGHT		"\033[48m"	//9

char *ansi_text_colors[] = {
	ANSI_RESET,
	ANSI_PRETO,
	ANSI_VERMELHO,
	ANSI_VERDE,
	ANSI_AMARELO,
	ANSI_AZUL,
	ANSI_ROSA,
	ANSI_CIANO,
	ANSI_BRANCO,
	ANSI_LIGHT,
	ANSI_PRETOL,
	ANSI_VERMELHOL,
	ANSI_VERDEL,
	ANSI_AMARELOL,
	ANSI_AZULL,
	ANSI_ROSAL,
	ANSI_CIANOL,
	ANSI_BRANCOL
};

char *ansi_background_colors[] = {
	ANSI_RESET,
	ANSI_BPRETO,
	ANSI_BVERMELHO,
	ANSI_BVERDE,
	ANSI_BLARANJA,
	ANSI_BAZUL,
	ANSI_BROSA,
	ANSI_BCIANO,
	ANSI_BBRANCO,
	ANSI_BLIGHT
};

char *ansi_effects[] = {
	ANSI_VAZIO,
	ANSI_BOLD,
	ANSI_SUBT,
	ANSI_BLINK
};









//************************************************************* ANTIGO, descontinuar apos terminar

// ANSI-Cores
#define		 RESET		"\033[00m"	//0
#define		 VAZIO		""			// NULL

#define		CLRSCR		"\033c"		// limpar a tela

// FORMATACAO
#define		 BOLD		"\033[1m" 	// negrito
#define		 SUBT		"\033[4m" 	// sublinhado
#define		 BLINK		"\033[5m" 	// piscando


// TEXT COLOR
#define 	PRETO		"\033[30m"	//1
#define 	VERMELHO	"\033[31m"	//2
#define 	VERDE		"\033[32m"	//3
#define 	AMARELO		"\033[33m"	//4
#define 	AZUL		"\033[34m"	//5
#define 	ROSA		"\033[35m"	//6
#define 	CIANO		"\033[36m"	//7
#define 	BRANCO		"\033[39m"	//8
#define 	LIGHT		"\033[38m"	//9

// TEXT COLOR LIGHT
#define 	PRETOL		"\033[90m"	//10
#define 	VERMELHOL	"\033[91m"	//11
#define 	VERDEL		"\033[92m"	//12
#define 	AMARELOL	"\033[93m"	//13
#define 	AZULL		"\033[94m"	//14
#define 	ROSAL		"\033[95m"	//15
#define 	CIANOL		"\033[96m"	//16
#define 	BRANCOL		"\033[99m"	//17

// BACKGROUD
#define 	BPRETO		"\033[40m"	//1
#define 	BVERMELHO	"\033[41m"	//2
#define 	BVERDE		"\033[42m"	//3
#define 	BLARANJA	"\033[43m"	//4
#define 	BAZUL		"\033[44m"	//5
#define 	BROSA		"\033[45m"	//6
#define 	BCIANO		"\033[46m"	//7
#define 	BBRANCO		"\033[47m"	//8
#define 	BLIGHT		"\033[48m"	//9

// BACKGROUD
#define 	BPRETO		"\033[40m"	//1
#define 	BVERMELHO	"\033[41m"	//2
#define 	BVERDE		"\033[42m"	//3
#define 	BLARANJA	"\033[43m"	//4
#define 	BAZUL		"\033[44m"	//5
#define 	BROSA		"\033[45m"	//6
#define 	BCIANO		"\033[46m"	//7
#define 	BBRANCO		"\033[47m"	//8
#define 	BLIGHT		"\033[48m"	//9

char *text_colors[] = {
	RESET,
	PRETO,
	VERMELHO,
	VERDE,
	AMARELO,
	AZUL,
	ROSA,
	CIANO,
	BRANCO,
	LIGHT,
	PRETOL,
	VERMELHOL,
	VERDEL,
	AMARELOL,
	AZULL,
	ROSAL,
	CIANOL,
	BRANCOL
};

char *background_colors[] = {
	RESET,
	BPRETO,
	BVERMELHO,
	BVERDE,
	BLARANJA,
	BAZUL,
	BROSA,
	BCIANO,
	BBRANCO,
	BLIGHT
};

char *effects[] = {
	VAZIO,
	BOLD,
	SUBT,
	BLINK
};







#endif
// fim do _LIBTOOLBOX_H








