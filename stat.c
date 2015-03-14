#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "stat.h"

#define INIT_TAB_STAT_SIZE 100

static tree_stat y = NULL;
static tab_words ty = NULL;
static tree_stat g = NULL;
static tab_words tg = NULL;


tree_stat insert_stat( tab_words tmpx, tree_stat t, char * word ) {
	if( t == NULL ) {
		word_t * n = malloc( sizeof *n );
		n->word = strdup(word);
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
	}
	tmpx->tab_words[tmpx->number] = x;
	tmpx->number++;
}

void stat_add_word(char * word){
	if (ty == NULL){
		ty = malloc(sizeof * ty);
		ty->tab_words = malloc ( INIT_TAB_STAT_SIZE * sizeof * ty->tab_words);
		ty->number = 0;
		ty->size = INIT_TAB_STAT_SIZE;
	}
	y = insert_stat(ty, y, word);
}

void stat_add_ngram(char** prefix,char * suffix){
	if (tg == NULL){
		tg = malloc(sizeof * tg);
		tg->tab_words = malloc ( INIT_TAB_STAT_SIZE * sizeof * tg->tab_words);
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

void write_tab(tab_words tmpx, FILE * out, int amount){
	int x = amount < tmpx->number ? amount : tmpx->number;
	int i;
	for( i=0; i < x ; i++){
		fprintf(out,"%7d %s\n", tmpx->tab_words[i]->counter, tmpx->tab_words[i]->word);
	}
	fprintf(out,"\n");
}

void write_stat( char * name_file_stat){
	if (name_file_stat != NULL) {
		FILE *out = fopen(name_file_stat, "w");
		qsort(ty->tab_words,ty->number,sizeof * ty->tab_words,cmp_stat);
		qsort(tg->tab_words, tg->number, sizeof * tg->tab_words, cmp_stat);
		write_tab(ty, out, 10);
		write_tab(tg,out, 10);
		fclose(out);
	} else
		return;
}

int cmp_stat(const void * a, const void * b){
	tree_stat na = *(tree_stat*) a;
	tree_stat nb = *(tree_stat*) b;
	 
	return nb->counter - na->counter;
}	
	
	
	
void print_tree_stat( tree_stat t, FILE *out, char *formater( const tree_stat x ) ) {
	if( t != NULL ) {
			if( t->right != NULL )
				print_tree_stat( t->right, out, formater );
			fprintf( out, "%s\n", formater( t ) );
			if( t->left != NULL )
				print_tree_stat( t->left, out, formater );
	}
}

char * fmt_stat( const tree_stat x ) {
	static char buf[10000];
	strcpy(buf,"");
	sprintf(buf,"%s\t%d",x->word,x->counter);
	return buf;
}









