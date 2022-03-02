CC = gcc
ARGS = -Wall -std=c99 -O3
APPNAME = tavoitetaso

$(APPNAME): main.o lib.o
	$(CC) main.o lib.o -o $(APPNAME) $(ARGS)

main.o: main.c
	$(CC) -c main.c $(ARGS)

lib.o: lib.c
	$(CC) -c lib.c $(ARGS)

clean:
	rm *.o $(APPNAME)
