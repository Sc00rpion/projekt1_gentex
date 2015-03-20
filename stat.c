#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "stat.h"
#include <math.h>

#define INIT_TAB_STAT_SIZE 100

static tree_stat y = NULL;
static tab_words ty = NULL;
static tree_stat g = NULL;
static tab_words tg = NULL;
static int all_words = 0;


tree_stat insert_stat( tab_words tmpx, tree_stat t, char * word ) {
	if( t == NULL ) {
		word_t * n = malloc( sizeof *n );
		fatal(n == NULL , "Nie udało się przydzielić pamięci");
		n->word = strdup(word);
		fatal(n->word == NULL , "Nie udało się przydzielić pamięci");
		n->counter = 1;
		n->left = n-> right = NULL;
		add_tab_word(tmpx, n);
		return n;
	} else if( strcmp(t->word,word) > 0  ) {
		t->left = insert_stat(tmpx, t->left, word );
		return t;
	} else if( strcmp(t->word,word) < 0 ) { 
		t->right = insert_stat(tmpx, t->right, word );
		return t;
	} else { 
		(t->counter)++;
		return t;
	}
}

void add_tab_word(tab_words tmpx, tree_stat x){
	if (tmpx->size <= tmpx->number){
		tmpx->size *=2;
		tmpx->tab_words = realloc (tmpx->tab_words, tmpx->size * sizeof * tmpx->tab_words);
		fatal(tmpx->tab_words == NULL , "Nie udało się przydzielić pamięci");
	}
	tmpx->tab_words[tmpx->number] = x;
	tmpx->number++;
}

void stat_add_word(char * word){
	if (ty == NULL){
		ty = malloc(sizeof * ty);
		fatal(ty == NULL , "Nie udało się przydzielić pamięci");
		ty->tab_words = malloc ( INIT_TAB_STAT_SIZE * sizeof * ty->tab_words);
		fatal(ty->tab_words == NULL , "Nie udało się przydzielić pamięci");
		ty->number = 0;
		ty->size = INIT_TAB_STAT_SIZE;
	}
	y = insert_stat(ty, y, word);
	all_words++;
}

void stat_add_ngram(char** prefix,char * suffix){
	if (tg == NULL){
		tg = malloc(sizeof * tg);
		fatal(tg == NULL , "Nie udało się przydzielić pamięci");
		tg->tab_words = malloc ( INIT_TAB_STAT_SIZE * sizeof * tg->tab_words);
		fatal(tg->tab_words == NULL , "Nie udało się przydzielić pamięci");
		tg->number = 0;
		tg->size = INIT_TAB_STAT_SIZE;
	}
	int mark = get_mark();
	char buf[10000];
	int i;
	strcpy(buf, "");
	for(i=0; i < mark; i++){
		strcat(buf, prefix[i]);
		strcat(buf, " ");
	}
	strcat(buf, suffix);
	g = insert_stat(tg, g, buf);
}

void write_tab_ty( FILE * out, int amount){
	int x = amount < ty->number ? amount : ty->number;
	int i;
	fprintf(out,"%7s %-20s %-6s\n","l.wys","n-gram", "prawdopodobieństwo");
	for( i=0; i < x ; i++){
		double probability = get_probability(y, ty->tab_words[i]->word);
		fprintf(out,"%7d %-20s\t%-6.5g \n", ty->tab_words[i]->counter, ty->tab_words[i]->word, probability);
	}
	fprintf(out,"\n");
}

void write_tab_tg( FILE * out, int amount){
	int x = amount < tg->number ? amount : tg->number;
	int i;
	fprintf(out,"%7s %-20s %-6s \t %s\n","l.wys","n-gram", "prawdopodobieństwo","PMI");
	for( i=0; i < x ; i++){
		double probability = get_probability(g, tg->tab_words[i]->word);
		long double pmi = get_pmi(tg->tab_words[i]->word);
		fprintf(out,"%7d %-20s\t%-6.5g\t\t %-6.5g \n", tg->tab_words[i]->counter, tg->tab_words[i]->word, probability, pmi);
	}
	fprintf(out,"\n");
}

double get_probability(tree_stat t, char * word){
	double m = search_word(t, word);
	fatal(all_words == 0 , "Nie wolno dzielić przez zero - all_words = 0");
	return m / all_words;
}

long double get_pmi(char* wngram){
	long double mx = 1;
	char buf[1000];
	int i, mark = get_mark();
	for ( i = 0; i <= mark; i++){
		strcpy(buf,"");
		fatal( sscanf(wngram,"%s",buf) != 1, "Błąd ilości słów w prefiksie");
		mx *= get_probability(y, buf);
	}
	fatal(mx == 0, "Błąd dzielenia przez zero");
	return logl(get_probability(g, wngram) / mx);
}

int search_word(tree_stat t, char * word){
	if( t == NULL ) {
		return NULL;
	} else if( strcmp(t->word,word) > 0  ) {
		return search_word(t->left, word );
	} else if( strcmp(t->word,word) < 0 ) { 
		return search_word(t->right, word );
	} else { 
		return t->counter;
	}
}



void write_stat( char * name_file_stat){
	if (name_file_stat != NULL) {
		FILE *out = fopen(name_file_stat, "a");
		fatal(out == NULL , "Nie udało utworzyć pliku statystyk");
		qsort(ty->tab_words,ty->number,sizeof * ty->tab_words,cmp_stat);
		qsort(tg->tab_words, tg->number, sizeof * tg->tab_words, cmp_stat);
		write_tab_ty(out, 10);
		write_tab_tg(out, 10);
		fclose(out);
		free_all_stat();
	} else
		return;
}

int cmp_stat(const void * a, const void * b){
	tree_stat na = *(tree_stat*) a;
	tree_stat nb = *(tree_stat*) b;
	 
	return nb->counter - na->counter;
}	
	
	
	
void free_tree_stat(tree_stat t) {
	if( t != NULL ) {
			if( t->right != NULL )
				free_tree_stat( t->right );
			free(t->right);
			free(t->word);
			if( t->left != NULL )
				free_tree_stat( t->left );
			free(t->left);
			free(t);
	} else
		free(t);
}

void free_tab_words(tab_words t){
	int i;
	for( i=0; i < t->number; i++){
		free(t->tab_words[i]->word);
		free(t->tab_words[i]);
	}
	free(t->tab_words);
	free(t);
}

void free_all_stat(){
	free_tab_words(ty);
	free_tab_words(tg);	
	y = NULL;
	ty = NULL;
	g = NULL;
	tg = NULL;
	all_words = 0;
}

char * fmt_stat( const tree_stat x ) {
	static char buf[10000];
	strcpy(buf,"");
	sprintf(buf,"%s\t%d",x->word,x->counter);
	return buf;
}









