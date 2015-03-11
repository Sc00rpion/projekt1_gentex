#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "store.h"
#include "managment.h"

#define INIT_NGRAM_SIZE 10
#define INIT_TAB_SIZE 10

static int cmark;
static store *m = NULL;

void init (){ 
	cmark = mark();
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
		m->tab[i].prefix = malloc( cmark * sizeof * (m->tab[i].prefix));
	}
}
ngram* search_prefix( char ** prefix){
	if (m == NULL)
		init();
	long int i,j;
	for (i=0; i < m->number_gram; i++)
		for (j=0; j < cmark ; j++){
			if (strcmp(prefix[j], m->tab[i].prefix[j]) == 0){
				if ( j == (cmark-1)) 
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
		for ( i=0; i<cmark; i++){
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
		for (j=0; j < cmark; j++)
			printf("%s ",m->tab[i].prefix[j]);
		printf("- ");
		for (j=0; j < m->tab[i].n_s; j++)
			printf("%s ",m->tab[i].suffix[j]);
		printf("\n");
	}
}
