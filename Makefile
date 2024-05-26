number=7

all:
	gcc main.c liste.c cozi.c stive.c -o lanParty -Wall
run:
	./lanParty date/t$(number)/c.in date/t$(number)/d.in r.out
clean:
	rm -f lanParty r.out
valgrind:
	valgrind --leak-check=full ./lanParty date/t$(number)/c.in date/t$(number)/d.in r.out