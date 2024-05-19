build:
	gcc main.c liste.c -o lanParty
run:
	./lanParty date/t4/c.in date/t4/d.in r.out
clean:
	rm -f lanParty