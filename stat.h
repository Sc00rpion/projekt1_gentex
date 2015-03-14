#ifndef _STAT_
#define _STAT_




typedef struct words {
	char* word;
	int counter;
	struct words *left, *right;
} word_t, *tree_stat;

typedef struct {
	tree_stat * tab_words;
	int number;
	int size;
} *tab_words;

tree_stat insert_stat(tab_words tmp, tree_stat t, char * word );

void stat_add_word(char * word);

void write_stat(char* name_file_stat);

void print_tree_stat( tree_stat t, FILE *out, char *formater( const tree_stat x ) ) ;

char * fmt_stat( const tree_stat x );

int cmp_stat(const void * a, const void * b);

void write_tab(tab_words tmp, FILE * out, int amount);

void add_tab_word(tab_words tmp, tree_stat x);

void stat_add_ngram(char** prefix,char * suffix);

#endif





