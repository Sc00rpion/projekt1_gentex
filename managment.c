#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "store.h"
#include "managment.h"
#include "reading.h"
#include "generation.h"

static char* 	name_file_out 		= NULL;
static int		number_words 		= 200;
static int		number_paragraphs 	= 0;
static int		number_gram			= 1;
static char*	name_file_stat		= NULL;
static char*	name_file_backup_out= NULL;
static char*	name_file_backup_in	= NULL;

char* get_name_file_out(){
	return name_file_out;
}

int get_mark(){
	return number_gram;
}
void set_mark(int mark){
	number_gram = mark;
}

int get_number_words(){
	return number_words;
}

int get_nuber_paragraphs(){
	return number_paragraphs;
}

char* get_name_file_stat(){
	return name_file_stat;
}

char* get_name_file_backup_out(){
	return name_file_backup_out;
}

char* get_name_file_backup_in(){
	return name_file_backup_in;
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

void test(int argc, int counter, char* string){
	if ( counter+1 >= argc ){
		printf("Błędne wywołanie : %s\n\n",string);
		info();
	}
}

int main( int argc, char **argv){
	if (argc < 2 ){
		fprintf(stderr,"Podano za mało argumentów\n\n");
		info();
	} else {
		int counter = 1;
		while ( counter < argc ){
			if (!strcmp(argv[counter],"-o")){
				test(argc, counter,"Nie podano nazwy pliku do zapisu");
				name_file_out = strdup(argv[counter+1]); 
			} 
			else if (!strcmp(argv[counter],"-s")){
				test(argc, counter,"Nie podano liczby słów");
				number_words = atoi(argv[counter+1]);
			} 
			else if (!strcmp(argv[counter],"-a")){
				test(argc, counter,"Nie podano liczby akapitów");
				number_paragraphs = atoi(argv[counter+1]);			
			} 
			else if (!strcmp(argv[counter],"-n")){
				test(argc, counter,"Nie podano rzędu n-gramów");
				number_gram = atoi(argv[counter+1]) - 1;			
			} 
			else if (!strcmp(argv[counter],"-stat")){
				test(argc, counter,"Nie podano nazwy pliku do zapisu statystyk");
				name_file_stat = strdup(argv[counter+1]); 			
			} 
			else if (!strcmp(argv[counter],"-pout")){
				test(argc, counter,"Nie podano nazwy pliku do zapisu pliku pośredniego");
				name_file_backup_out = strdup(argv[counter+1]); 			
			} 
			else if (!strcmp(argv[counter],"-pin")){
				test(argc, counter,"Nie podano nazwy pliku pośredniego");
				name_file_backup_in = strdup(argv[counter+1]); 			
			} 
			else
				break;
				
			counter= counter + 2;
		}
		if (name_file_backup_in == NULL)
			test(argc, counter-1,"Nie podano plików do analizy");
		for ( ; counter < argc; counter++)
			reading(argv[counter]);
		backup();
		generation();
		store * x = get_m();
		// print_tree( x->t, stdout, 4, fmt );
		printf(" %d\n", x->number_gram);
		write_stat(name_file_stat);
	}
	return 0;
}