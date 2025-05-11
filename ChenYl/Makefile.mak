CC = gcc
CFLAGS = -Wall -Wextra -IchenYl.h

SRC = chenYl.c/main.c chenYl.c/animal.c chenYl.c/gestion_animaux.c

EXEC = chenyl

all:
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

clean:
	rm -f $(EXEC)

run: all
	./$(EXEC)
