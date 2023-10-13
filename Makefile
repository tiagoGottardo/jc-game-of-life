CC = gcc
CFLAGS = -c -Wall
LFLAGS = -Wall
LIBS = -lm -lncurses 

main: main.c
	$(CC) $(LFLAGS) -o app main.c $(LIBS)

lib: $(FILES)
	echo "$(CC)"

clean:
	rm -f *.o main

.PHONY: main
