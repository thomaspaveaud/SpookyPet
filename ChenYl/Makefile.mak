chenyl: chenYl.c/main.c chenYl.c/animal.c chenYl.c/gestion_animaux.c
	gcc -Wall -Wextra -IchenYl.h -o chenyl \
	    chenYl.c/main.c \
	    chenYl.c/animal.c \
	    chenYl.c/gestion_animaux.c

clean:
	rm -f chenyl

run: chenyl
	./chenyl