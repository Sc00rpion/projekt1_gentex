#include <stdio.h>
#include <stdlib.h>
#include "store.h"
#include "managment.h"
#include "reading.h"

int mark(){
	return 3;
}

int main( int argc, char **argv){
		// char *t = "ala";
		// char *r = "kot";
		// char * s = "pies";
		// add(&t,"asia");
		// add(&r,"asia");
		// add(&s,"atra");
		// add(&s,"pppp");
		// add(&r,"www");
		// add(&t,"qqq");		
		// print_all();
		// printf("\n\n");
		
		reading("test.txt");
		print_all();
	
	
	return 0;
}