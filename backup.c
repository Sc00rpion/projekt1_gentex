#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "store.h"
#include "managment.h"
#include "reading.h"
#include "generation.h"
#include <time.h>

#define INIT_SIZE_SUFFIX 4000

static int mark;

void backup(){
	if (get_name_file_backup_out() == NULL && get_name_file_backup_in() == NULL)
		return;
	store* m = get_m();
	mark = get_mark();
	if (get_name_file_backup_in() != NULL && m == NULL){
		FILE *in = fopen(get_name_file_backup_in(),"r");
		char buf[INIT_SIZE_BUF];
		int i,j,n_s, number_gram;
		fscanf(in,"%d %d",&mark, &number_gram);
		set_mark(mark);

		char **prefix = malloc(mark * sizeof * prefix); 
		for(i = 0; i < mark; i++)
			prefix[i] = malloc(INIT_SIZE_BUF *sizeof * prefix[i]);
			
		char **suffix = malloc(INIT_SIZE_SUFFIX * sizeof * suffix); 
		for(i = 0; i < INIT_SIZE_SUFFIX; i++)
			suffix[i] = malloc(INIT_SIZE_BUF *sizeof * suffix[i]);
		for (j=0; j < number_gram; j++){
			for (i=0; i < mark; i++){
				fscanf(in,"%s",buf);
				strcpy(prefix[i],buf);
			}
			fscanf(in,"%d",&n_s);
			if (n_s >= 2* INIT_SIZE_BUF)
				printf("aaaaaaaaaaaaaaaaa");
			for (i=0; i < n_s; i++){
				fscanf(in,"%s",buf);
				strcpy(suffix[i], buf);
			}
			add_from_backup(prefix, suffix, n_s);
		}
		fclose(in);
	}
	else{
		FILE *out = fopen(get_name_file_backup_out(),"w");
		fprintf(out,"%d %d\n",mark, m->number_gram);
		long int i,j;
		for (i=0; i <m->number_gram; i++){
			for (j=0; j < mark; j++)
				fprintf(out,"%s ",m->tab[i].prefix[j]);
			fprintf(out,"%d ",m->tab[i].n_s);				
			for (j=0; j < m->tab[i].n_s; j++)
				fprintf(out,"%s ",m->tab[i].suffix[j]);
			fprintf(out,"\n");
		}
		fclose(out);
	}
}
