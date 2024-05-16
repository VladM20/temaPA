build:
	gcc main.c liste.c -o lanParty
run:
	./lanParty date/t1/c.in date/t1/d.in r.out
clean:
	rm -f lanParty