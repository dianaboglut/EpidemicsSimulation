all:
	@gcc -Wall -Wextra main.c include.c io.c simulation.c person.c -o test

debug:
	@gcc -DDEBUG -Wall -Wextra main.c include.c io.c simulation.c person.c -o test
