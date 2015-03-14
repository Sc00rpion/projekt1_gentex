#ifndef _STORE_
#define _STORE_

#define INIT_NGRAM_SIZE 10
#define INIT_TAB_SIZE 10
#define INIT_SUFFIX_SIZE 10

typedef struct {
	char ** prefix;
	char ** suffix;
	int size_s;
	int n_s;
} ngram;

typedef struct node {
	ngram * g;
	struct node *left, *right;
} node_t, *tree_t;


typedef struct {
	tree_t t;
	int number_gram;
	int size;
	ngram** tab;
	int n_s_max;
} store;

tree_t insert( tree_t t, char **prefix, char * suffix); 

store * get_m();

void print_tree( );

void add_tab(ngram * tmp);

char * fmt( const ngram *s );

void init ();

void init_ngram(node_t * n);

int cmp_prefix( char ** prefix, char ** prefix2 );

ngram* search_prefix( tree_t t, char ** prefix);

void add(char **prefix, char * suffix); 

void add_suffix(char* suffix, ngram* tmp);

void resize_suffix(ngram* tmp);

void resize_ngram();

void print_all();

ngram* rand_prefix();

char* rand_suffix( char** prefix);

#endif