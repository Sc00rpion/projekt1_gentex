#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reading.h"
#include "store.h"
#include "managment.h"


static int cmark;

void reading( char * name_file){
	FILE *in = fopen(name_file, "r");
	char buf[INIT_SIZE_BUF];
	cmark = mark();
	int i;
	char **prefix = malloc(cmark * sizeof * prefix); 
	for(i = 0; i < cmark; i++)
		prefix[i] = malloc(INIT_SIZE_BUF *sizeof * prefix[i]);
	
	for (i=0; i < cmark; i++){
		if (fscanf(in, "%s",buf) != 1)
			printf("Błąd");
		strcpy(prefix[i],buf);
	}
	while ( fscanf(in, "%s",buf) == 1 ){
		add(prefix,buf);
		for (i=1; i < cmark; i++)
			strcpy(prefix[i-1],prefix[i]);
		strcpy(prefix[cmark-1],buf);
	}			
}