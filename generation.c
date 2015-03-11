#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "store.h"
#include "managment.h"
#include "reading.h"
#include "generation.h"
#include <time.h>

void generation(){
	if (get_name_file_out() == NULL || get_m() == NULL)
		return;
	srand(time(NULL));
	int i, counter = 0;
	int mark = get_mark();
	char buf[INIT_SIZE_BUF];
	FILE *out = fopen(get_name_file_out(),"a");
	char **prefix = malloc(mark * sizeof * prefix); 
	for(i = 0; i < mark; i++)
		prefix[i] = malloc(INIT_SIZE_BUF *sizeof * prefix[i]);
		
	ngram* tmp =rand_prefix();
	
	for(i=0; i< mark;i++){
		strcpy(prefix[i],tmp->prefix[i]);
		fprintf(out,"%s ",prefix[i]);
		counter++;
	}
	while (counter < get_number_words()){
		strcpy(buf,rand_suffix(prefix));
		for (i=1; i < mark; i++)
			strcpy(prefix[i-1],prefix[i]);
	
		strcpy(prefix[mark-1],buf);
		counter++;
		fprintf(out,"%s ",buf);

	}
	fclose(out);
}
