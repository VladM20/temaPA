number=13

all: build
build:
	gcc -g main.c liste.c cozi.c stive.c tasks.c teams.c bst.c avl.c -o lanParty -Wall
run:
	./lanParty date/t$(number)/c.in date/t$(number)/d.in r.out
clean:
	rm -f lanParty r.out
valgrind:
	valgrind --leak-check=full --track-origins=yes ./lanParty date/t$(number)/c.in date/t$(number)/d.in r.out