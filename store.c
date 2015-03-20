#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "store.h"
#include "managment.h"


static int mark;
static store *m = NULL;

store * get_m(){
	return m;
}
void set_m(store * tmp){
	m = tmp;
}


void free_tree_store(tree_t t) {
	if( t != NULL ) {
			if( t->right != NULL )
				free_tree_store( t->right );
			if( t->left != NULL )
				free_tree_store( t->left );
			free(t);
	}
}

void free_tab(store * t){
	int i,j;
	for( i=0; i < t->number_gram; i++){
		
		for (j=0; j < mark; j++) 
			free(t->tab[i]->prefix[j]);
		free(t->tab[i]->prefix);
		for (j=0; j < t->tab[i]->n_s; j++) 
			free(t->tab[i]->suffix[j]);		
		free(t->tab[i]->suffix);
		free(t->tab[i]);
	}
	free(t->tab);
}

void free_all_store(){
	store * m = get_m();
	free_tab(m);
	free_tree_store(m->t);
	free(m);
	m = NULL;
}

tree_t insert( tree_t t, char **prefix, char * suffix ) {
	if( t == NULL ) {
		node_t * n = malloc( sizeof *n );
		fatal(n == NULL , "Nie udało się przydzielić pamięci");
		init_ngram(n);
		int i;
		for ( i=0; i < mark; i++){
			n->g->prefix[i] = strdup(prefix[i]);
			fatal(n->g->prefix[i] == NULL , "Nie udało się przydzielić pamięci");
		}
		add_suffix(suffix, n->g);
		add_tab(n->g);
		n->left = n-> right = NULL;
		return n;
	} else if( cmp_prefix(prefix,t->g->prefix) > 0  ) {
		t->left = insert( t->left, prefix, suffix );
		return t;
	} else if( cmp_prefix(prefix,t->g->prefix) < 0 ) { 
		t->right = insert( t->right, prefix, suffix );
		return t;
	} else { 
		add_suffix(suffix, t->g);
		return t;
	}
}

void add_tab(ngram* tmp){
	resize_ngram();
	m->tab[m->number_gram] = tmp;
	(m->number_gram)++;
}


void add(char **prefix, char * suffix){ 
	if (m == NULL)
		init();
	m->t = insert(m->t, prefix, suffix);
}

void print_tree( tree_t t, FILE *out, int d, char *formater( const ngram *x ) ) {
	if( t != NULL ) {
			if( t->right != NULL )
				print_tree( t->right, out, d+1, formater );
			fprintf( out, "%s\n", formater( t->g ) );
			if( t->left != NULL )
				print_tree( t->left, out, d+1, formater );
	}
}

char * fmt( const ngram *s ) {
	static char buf[10000000];
	int i;
	strcpy(buf,"");
	for (i = 0; i < mark ; i++){
		strcat(buf,s->prefix[i]);
		strcat(buf, " ");
	}
	
	return buf;
}

void init_ngram(node_t * n){
	n->g = malloc( sizeof * n->g);
	fatal(n->g == NULL , "Nie udało się przydzielić pamięci");
	n->g->n_s = 0;
	n->g->size_s = INIT_SUFFIX_SIZE;
	n->g->prefix = malloc( mark * sizeof * n->g->prefix);
	fatal(n->g->prefix == NULL , "Nie udało się przydzielić pamięci");
	n->g->suffix = malloc( INIT_SUFFIX_SIZE * sizeof * n->g->suffix);
	fatal(n->g->suffix == NULL , "Nie udało się przydzielić pamięci");
}
 
void init (){ 
	mark = get_mark();
	m = malloc( sizeof *m);
	fatal(m == NULL , "Nie udało się przydzielić pamięci");
	m->t = NULL;
	m->number_gram = 0;
	m->n_s_max = 0;
	m->size = INIT_TAB_SIZE;
	m->tab = malloc( INIT_TAB_SIZE * sizeof * (m->tab) );
	fatal( m->tab == NULL , "Nie udało się przydzielić pamięci");
}
int cmp_prefix( char ** prefix, char ** prefix2 ){
	int i,j;
	for (j=0; j < mark ; j++){
		i = strcmp(prefix[j], prefix2[j]);
		if (i == 0){
			if ( j == (mark-1)) 
				return 0;
		} 
		else if ( i < 0 )
			return -1;
		else
			return 1;
	}
		
}

void add_from_backup(char **prefix, char **suffix, int n_s){ 
	int i;
	for ( i=0; i < n_s; i++)
	add( prefix,suffix[i] );
	
}

void add_suffix(char* suffix, ngram* tmp){
	resize_suffix(tmp);
	tmp->suffix[tmp->n_s] = strdup(suffix);
	fatal(tmp->suffix[tmp->n_s] == NULL , "Nie udało się przydzielić pamięci");
	(tmp->n_s)++;
	if (tmp->n_s > m->n_s_max)
		m->n_s_max = tmp->n_s;
}

void resize_suffix(ngram* tmp){
	if ( tmp->n_s >= tmp->size_s ){
		tmp->size_s *= 2;
		tmp->suffix = realloc(tmp->suffix, tmp->size_s * sizeof * (tmp->suffix));
		fatal( tmp->suffix == NULL , "Nie udało się przydzielić pamięci");
	}
}

void resize_ngram(){
	if ( m->number_gram >= m->size){
		m->size *= 2;
		m->tab = realloc( m->tab, m->size * sizeof * (m->tab) );
		fatal( m->tab == NULL , "Nie udało się przydzielić pamięci");
	}
}

ngram* rand_prefix(){
	return m->tab[rand() % m->number_gram];
}

char* rand_suffix(char** prefix){
	ngram* tmp;
	tree_t t = m->t;
	tmp = search_prefix(t,prefix);
	return tmp->suffix[rand() % tmp->n_s];
}

ngram* search_prefix(tree_t t, char ** prefix ) {
	if( cmp_prefix(prefix,t->g->prefix) == 0 ) {
		return t->g;
	} else if( cmp_prefix(prefix,t->g->prefix) > 0  ) {
		return search_prefix( t->left, prefix);
	} else if( cmp_prefix(prefix,t->g->prefix) < 0 ) { 
		return search_prefix(t->right, prefix );
	} else { 
		return NULL;
	}
}
















