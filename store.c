#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "store.h"
#include "managment.h"


static int mark;
static store *m = NULL;

void init (){ 
	mark = get_mark();
	m = malloc( sizeof *m);
	m->number_gram = 0;
	m->size = INIT_TAB_SIZE;
	m->tab = malloc( INIT_TAB_SIZE * sizeof * (m->tab) );
	long int i;
	for ( i=0 ; i < INIT_TAB_SIZE ; i++){
		m->tab[i].size_s = INIT_NGRAM_SIZE;
		m->tab[i].n_s = 0;
		m->tab[i].suffix = malloc( INIT_NGRAM_SIZE * sizeof * (m->tab[i].suffix));
		m->tab[i].n_p = 0;
		m->tab[i].prefix = malloc( mark * sizeof * (m->tab[i].prefix));
	}
}
ngram* search_prefix( char ** prefix){
	if (m == NULL)
		init();
	long int i,j;
	for (i=0; i < m->number_gram; i++)
		for (j=0; j < mark ; j++){
			if (strcmp(prefix[j], m->tab[i].prefix[j]) == 0){
				if ( j == (mark-1)) 
					return &(m->tab[i]);
			} else
				break;
		}		
	return NULL;
}

void add(char **prefix, char * suffix){ 
	ngram* tmp;
	if (m == NULL)
		init();
	if ((tmp = search_prefix(prefix)) == NULL){
		resize_ngram();
		long int i;
		for ( i=0; i<mark; i++){
			m->tab[m->number_gram].prefix[i] = strdup(prefix[i]);
			(m->tab[m->number_gram].n_p)++;	
		}
		add_suffix(suffix, &(m->tab[m->number_gram]));
		(m->number_gram)++;
		
	} else {
	add_suffix(suffix, tmp);
	}
}

void add_suffix(char* suffix, ngram* tmp){
	resize_suffix(tmp);
	tmp->suffix[tmp->n_s] = strdup(suffix);
	(tmp->n_s)++;
}

void resize_suffix(ngram* tmp){
	if ( tmp->n_s == tmp->size_s ){
		tmp->size_s *= 2;
		tmp->suffix = realloc(tmp->suffix, tmp->size_s * sizeof * (tmp->suffix));
	}
}

void resize_ngram(){ // powiększa główną listę
	if ( m->number_gram >= m->size){
		long int old_size = m->size;
		m->size *= 2;
		m->tab = realloc( m->tab, m->size * sizeof * (m->tab) );
		long int i;
		for ( i=old_size ; i < m->size ; i++){
			m->tab[i].size_s = INIT_NGRAM_SIZE;
			m->tab[i].n_s = 0;
			m->tab[i].suffix = malloc( INIT_NGRAM_SIZE * sizeof * (m->tab[i].suffix));
			m->tab[i].n_p = 0;
			m->tab[i].prefix = malloc( INIT_NGRAM_SIZE * sizeof * (m->tab[i].prefix));
		}
	}
}

void print_all(){ // do testów
	long int i,j;
	for (i=0; i <m->number_gram; i++){
		for (j=0; j < mark; j++)
			printf("%s ",m->tab[i].prefix[j]);
		printf("- ");
		for (j=0; j < m->tab[i].n_s; j++)
			printf("%s ",m->tab[i].suffix[j]);
		printf("\n");
	}
}

ngram* rand_prefix(){
	srand(time(NULL));
	return &(m->tab[rand() % m->number_gram]);
}

char* rand_suffix(char** prefix){
	srand(time(NULL));
	ngram* tmp;
	tmp = search_prefix(prefix);
	return tmp->suffix[rand() % tmp->n_s];
}


















