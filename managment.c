#include <stdio.h>
#include <stdlib.h>
#include "store.h"

int mark(){
	return 1;
}

int main( int argc, char **argv){
		char *t = "ala";
		char *r = "kot";
		char * s = "pies";
		add(&t,"asia");
		add(&r,"asia");
		add(&s,"atra");
		add(&s,"pppp");
		add(&r,"www");
		add(&t,"qqq");		
		print_all();
	
	
	return 0;
}