#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reading.h"
#include "store.h"
#include "managment.h"
#include "stat.h"
#include "error.h"


static int mark;

void reading( char * name_file){
	FILE *in = fopen(name_file, "r");
	fatal(in == NULL, "Nie udało się odczytać pliku do analizy");
	char buf[INIT_SIZE_BUF];
	mark = get_mark();
	int i;
	char **prefix = malloc(mark * sizeof * prefix); 
	fatal(prefix == NULL , "Nie udało się przydzielić pamięci");
	for(i = 0; i < mark; i++)
		prefix[i] = malloc(INIT_SIZE_BUF *sizeof * prefix[i]);
		
	if (get_name_file_stat() == NULL){
		for (i=0; i < mark; i++){
			fatal(fscanf(in, "%s",buf) != 1, "Zbyt krótki plik do analizy");
			strcpy(prefix[i],buf);
		}
		while ( fscanf(in, "%s",buf) == 1 ){
			add(prefix,buf);
			for (i=1; i < mark; i++)
				strcpy(prefix[i-1],prefix[i]);
			strcpy(prefix[mark-1],buf);
		}
	} else {
		for (i=0; i < mark; i++){
			fatal(fscanf(in, "%s",buf) != 1, "Zbyt krótki plik do analizy");
			strcpy(prefix[i],buf);
			stat_add_word(buf);
		}
		while ( fscanf(in, "%s",buf) == 1 ){
			add(prefix,buf);
			stat_add_ngram(prefix, buf);
			stat_add_word(buf);
			for (i=1; i < mark; i++)
				strcpy(prefix[i-1],prefix[i]);
			strcpy(prefix[mark-1],buf);
			
		}
		
	}
	for ( i=0; i<mark; i++)
		free(prefix[i]);
	free(prefix);
	fclose(in);
}

void reading_stat( char * name_file){
	FILE *in = fopen(name_file, "r");
	fatal(in == NULL, "Nie udało się odczytać pliku do analizy");
	char buf[INIT_SIZE_BUF];
	mark = get_mark();
	int i;
	char **prefix = malloc(mark * sizeof * prefix); 
	fatal(prefix == NULL , "Nie udało się przydzielić pamięci");
	for(i = 0; i < mark; i++)
		prefix[i] = malloc(INIT_SIZE_BUF *sizeof * prefix[i]);
		for (i=0; i < mark; i++){
			fatal(fscanf(in, "%s",buf) != 1, "Zbyt krótki plik do analizy");
			strcpy(prefix[i],buf);
			stat_add_word(buf);
		}
		while ( fscanf(in, "%s",buf) == 1 ){
			stat_add_ngram(prefix, buf);
			stat_add_word(buf);
			for (i=1; i < mark; i++)
				strcpy(prefix[i-1],prefix[i]);
			strcpy(prefix[mark-1],buf);
			
		}
	for ( i=0; i<mark; i++)
		free(prefix[i]);
	free(prefix);
	fclose(in);
}
