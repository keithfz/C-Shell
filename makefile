all: shell402 create list
shell402: shell402.o shellFunctions.o input.o
	gcc shell402.o shellFunctions.o input.o -o shell402
shell402.o: shell402.c
	gcc -c shell402.c
shellFunctions.o: shellFunctions.c
	gcc -c shellFunctions.c
input.o: input.c
	gcc -c input.c
create: create.o createFunctions.o
	gcc create.o createFunctions.o -o create
create.o: create.c
	gcc -c create.c
createFunctions.o: createFunctions.c
	gcc -c createFunctions.c
list: list.o listFunctions.o
	gcc list.o listFunctions.o -o list
list.o: list.c
	gcc -c list.c
listFunctions.o: listFunctions.c
	gcc -c listFunctions.c
clean:
	rm -rf core *.o list create shell402
