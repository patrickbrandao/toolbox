#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

char *repl_str(const char *str, const char *from, const char *to) {
	// Adjust each of the below values to suit your needs.

	// Increment positions cache size initially by this number.
	size_t cache_sz_inc = 16;

	// Thereafter, each time capacity needs to be increased,
	// multiply the increment by this factor.
	const size_t cache_sz_inc_factor = 3;

	// But never increment capacity by more than this number.
	const size_t cache_sz_inc_max = 1048576;

	char *pret, *ret = NULL;
	const char *pstr2, *pstr = str;
	size_t i, count = 0;
	ptrdiff_t *pos_cache = NULL;
	size_t cache_sz = 0;
	size_t cpylen, orglen, retlen, tolen, fromlen = strlen(from);

	// Find all matches and cache their positions.
	while ((pstr2 = strstr(pstr, from)) != NULL) {
		count++;

		// Increase the cache size when necessary.
		if (cache_sz < count) {
			cache_sz += cache_sz_inc;
			pos_cache = realloc(pos_cache, sizeof(*pos_cache) * cache_sz);
			if (pos_cache == NULL) {
				goto end_repl_str;
			}
			cache_sz_inc *= cache_sz_inc_factor;
			if (cache_sz_inc > cache_sz_inc_max) {
				cache_sz_inc = cache_sz_inc_max;
			}
		}

		pos_cache[count-1] = pstr2 - str;
		pstr = pstr2 + fromlen;
	}

	orglen = pstr - str + strlen(pstr);

	// Allocate memory for the post-replacement string.
	if (count > 0) {
		tolen = strlen(to);
		retlen = orglen + (tolen - fromlen) * count;
	} else {
		retlen = orglen;
	}
	ret = malloc(retlen + 1);

	if (ret == NULL) {
		goto end_repl_str;
	}

	if (count == 0) {
		// If no matches, then just duplicate the string.
		strcpy(ret, str);
	} else {
		// Otherwise, duplicate the string whilst performing
		// the replacements using the position cache.
		pret = ret;
		memcpy(pret, str, pos_cache[0]);
		pret += pos_cache[0];
		for (i = 0; i < count; i++) {
			memcpy(pret, to, tolen);
			pret += tolen;
			pstr = str + pos_cache[i] + fromlen;
			cpylen = (i == count-1 ? orglen : pos_cache[i+1]) - pos_cache[i] - fromlen;
			memcpy(pret, pstr, cpylen);
			pret += cpylen;
		}
		ret[retlen] = '\0';
	}

end_repl_str:
	// Free the cache and return the post-replacement string,
	// which will be NULL in the event of an error.
	free(pos_cache);
	return ret;
}

void help_str_replace(){
	printf("Use: str_replace (string) (old-word) (new-word)\n");
	exit(1);
}

//int main(const int argc, const char **argv){
int main_str_replace(const char *progname, const int argc, const char **argv){
	register int i = 0;
	char *input_string = NULL;
    char *old_word = NULL;
    char *new_word = NULL;
    char *new = NULL;

    if(argc!=4) help_str_replace();

    // string contexto
    input_string = strdup(argv[1]);

    // antiga palavra
    old_word = strdup(argv[2]);

    // nova palavra
    new_word = strdup(argv[3]);


    new =repl_str(input_string, (const char *) old_word, (const char *) new_word);

    printf("%s\n", new);

	// nenhum item encontrado
	return 0;
}












