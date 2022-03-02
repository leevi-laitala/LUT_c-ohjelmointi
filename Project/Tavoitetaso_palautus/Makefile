CC = gcc
ARGS = -Wall -std=c99 -O3
APPNAME = tavoitetaso

$(APPNAME): HTTavoitetaso.o HTPerusKirjasto.o HTTavoiteKirjasto.o
	$(CC) HTTavoitetaso.o HTPerusKirjasto.o HTTavoiteKirjasto.o -o $(APPNAME) $(ARGS)

HTTavoitetaso.o: HTTavoitetaso.c
	$(CC) -c HTTavoitetaso.c $(ARGS)

HTPerusKirjasto.o: HTPerusKirjasto.c HTPerusKirjasto.h
	$(CC) -c HTPerusKirjasto.c $(ARGS)

HTTavoiteKirjasto.o: HTTavoiteKirjasto.c HTPerusKirjasto.h
	$(CC) -c HTTavoiteKirjasto.c $(ARGS)

clean:
	rm *.o $(APPNAME)
