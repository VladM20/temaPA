build:
	gcc main.c liste.c cozi.c stive.c -o lanParty -Wall
run:
	./lanParty date/t7/c.in date/t7/d.in r.out
clean:
	rm -f lanParty r.out