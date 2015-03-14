CC = cc -Wall -ggdb

gentex: managment.o reading.o store.o error.o generation.o backup.o stat.o
	$(CC) $^

managment.o: managment.h reading.h store.h generation.h error.h
reading.o: managment.h reading.h store.h error.h
store.o: managment.h store.h error.h
generation.o: managment.h store.h generation.h error.h
error.o: error.h
backup.o: managment.h store.h error.h
stat.o: stat.h
