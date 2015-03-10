#ifndef _STORE_
#define _STORE_


typedef struct {
	char ** prefix;
	int n_p;
	char ** suffix;
	int size_s;
	int n_s;
} ngram;

typedef struct {
	int number_gram;
	int size;
	ngram* tab;
} store;

void init ();

ngram* search_prefix( char ** prefix);

void add(char **prefix, char * suffix); 

void add_suffix(char* suffix, ngram* tmp);

void resize_suffix(ngram* tmp);

void resize_ngram();

void print_all();

#endif