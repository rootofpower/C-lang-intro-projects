# variables
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wno-vla-parameter
LDLIBS=-lm -lcurses
OUTPUT=spaceFighter

# targets
all: $(OUTPUT)

$(OUTPUT): spaceFighter.o main.o
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) spaceFighter.o main.o $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o

spaceFighter.o: Space_fighter.c Space_fighter.h
	$(CC) $(CFLAGS) -c Space_fighter.c $(LDLIBS) -o spaceFighter.o

# remove compiled files
clean: 
	rm -rf $(OUTPUT) *.o
