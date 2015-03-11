CC = cc -Wall -ggdb

gentex: managment.o reading.o store.o generation.o error.o backup.o
	$(CC) $^

managment.o: managment.h reading.h store.h generation.h error.h
reading.o: managment.h reading.h store.h error.h
store.o: managment.h store.h error.h
generation.o: managment.h store.h generation.h error.h
error.o: error.h
backup.o: managment.h store.h error.h
