#ifndef _STORE_
#define _STORE_

#define INIT_NGRAM_SIZE 10
#define INIT_TAB_SIZE 10

typedef struct {
	char ** prefix;
	long int n_p;
	char ** suffix;
	int size_s;
	int n_s;
} ngram;

typedef struct {
	long int number_gram;
	long int size;
	ngram* tab;
} store;

void init ();

ngram* search_prefix( char ** prefix);

void add(char **prefix, char * suffix); 

void add_suffix(char* suffix, ngram* tmp);

void resize_suffix(ngram* tmp);

void resize_ngram();

void print_all();

ngram* rand_prefix();

char* rand_suffix(char** prefix);

#endif