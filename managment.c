#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "store.h"
#include "managment.h"
#include "reading.h"

static char* 	name_file_out 		= NULL;
static int		number_words 		= 0;
static int		number_paragraphs 	= 0;
static int		number_gram			= 1;
static char*	name_file_stat		= NULL;
static char*	name_file_backup_out= NULL;
static char*	name_file_backup_in	= NULL;

int mark(){
	return 2;
}
void info(){
	printf(		"WYWOŁANIE\n"
				"gentex [opcje] plik bazowy1.txt plik bazowy2.txt ...\n\n"
				"OPCJE\n"
				"-o nazwa pliku \t\t-- Nazwa pliku gdzie ma byc zapisany wygenerowany tekst\n"
				"-s liczba słów \t\t-- Liczba słow z jakiej ma sie skladac wygenerowany tekst\n"
				"-a liczba akapitów \t-- Liczba akapitów z której składac ma sie wygenerowany tekst\n"
				"-n rzad n-gramów \t-- Rzad n-gramów w oparciu o który bedzie generowany tekst\n"
				"-stat nazwa pliku \t-- Generowanie statystyk tekstu bazowego i wynikowego zapisana do pliku\n");
	
	exit(EXIT_FAILURE);
}

void test(int argc, int licznik, char* string){
	if ( licznik+1 >= argc ){
		printf("Błędne wywołanie : %s\n\n",string);
		info();
	}
}

int main( int argc, char **argv){
	if (argc < 2 ){
		fprintf(stderr,"Podano za mało argumentów\n\n");
		info();
	} else {
		int licznik = 1;
		while ( licznik < argc ){
			if (!strcmp(argv[licznik],"-o")){
				test(argc, licznik,"Nie podano nazwy pliku do zapisu");
				name_file_out = strdup(argv[licznik+1]); 
			} 
			else if (!strcmp(argv[licznik],"-s")){
				test(argc, licznik,"Nie podano liczby słów");
				number_words = atoi(argv[licznik+1]);
			} 
			else if (!strcmp(argv[licznik],"-a")){
				test(argc, licznik,"Nie podano liczby akapitów");
				number_paragraphs = atoi(argv[licznik+1]);			
			} 
			else if (!strcmp(argv[licznik],"-n")){
				test(argc, licznik,"Nie podano rzędu n-gramów");
				number_gram = atoi(argv[licznik+1]);			
			} 
			else if (!strcmp(argv[licznik],"-stat")){
				test(argc, licznik,"Nie podano nazwy pliku do zapisu statystyk");
				name_file_stat = strdup(argv[licznik+1]); 			
			} 
			else if (!strcmp(argv[licznik],"-pout")){
				test(argc, licznik,"Nie podano nazwy pliku do zapisu pliku pośredniego");
				name_file_backup_out = strdup(argv[licznik+1]); 			
			} 
			else if (!strcmp(argv[licznik],"-pin")){
				test(argc, licznik,"Nie podano nazwy pliku pośredniego");
				name_file_backup_in = strdup(argv[licznik+1]); 			
			} 
			else
				break;
				
			licznik= licznik + 2;
		}
		if (name_file_backup_in == NULL)
			test(argc, licznik-1,"Nie podano plików do analizy");
		for ( ; licznik < argc; licznik++)
			reading(argv[licznik]);
		print_all();
	
	}
	return 0;
}