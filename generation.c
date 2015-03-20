#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "store.h"
#include "managment.h"
#include "reading.h"
#include "generation.h"
#include <time.h>
#include <ctype.h>

void generation(){
	if (get_name_file_out() == NULL || get_m() == NULL)
		return;
	srand(time(NULL));
	int i, counter_words = 0, counter_paragraphs = 0;
	int mark = get_mark();
	int paragraph = get_number_paragraphs();
	int words = get_number_words();
	char buf[INIT_SIZE_BUF];
	FILE *out = fopen(get_name_file_out(),"a");
	fatal(out == NULL, "Nie udało się otworzyć pliku do zapisu tekstu docelowego");
	char **prefix = malloc(mark * sizeof * prefix);
	fatal(prefix == NULL , "Nie udało się przydzielić pamięci");	
	for(i = 0; i < mark; i++){
		prefix[i] = malloc(INIT_SIZE_BUF *sizeof * prefix[i]);
		fatal(prefix[i] == NULL , "Nie udało się przydzielić pamięci");
	}
	ngram* tmp =rand_prefix();
	while (isalpha(tmp->prefix[0][0]) == 0)
		tmp = rand_prefix();
	
	for(i=0; i< mark;i++){
		strcpy(prefix[i],tmp->prefix[i]);
		if (i==0){
			strcpy(buf,tmp->prefix[i]);
			buf[0] = toupper(buf[0]);
			fprintf(out,"%s ",buf);
			counter_words++;
		} else{
			fprintf(out,"%s ",prefix[i]);
			counter_words++;
		}
	}
	while (counter_paragraphs < paragraph){
		while (counter_words < words){
			strcpy(buf,rand_suffix(prefix));
			for (i=1; i < mark; i++)
				strcpy(prefix[i-1],prefix[i]);
			strcpy(prefix[mark-1],buf);
			if (counter_words == 0)
				buf[0] = toupper(buf[0]);
			if (counter_words == words-1){
				if (isalpha(buf[strlen(buf)-1]))
					fprintf(out,"%s.",buf);
				else {
					counter_words--;
					fprintf(out,"%s ",buf);
				}
			} else
				fprintf(out,"%s ",buf);
			counter_words++;
		}
		counter_paragraphs++;
		fprintf(out,"\n\n");
		counter_words = 0;
	}
	fclose(out);
}
