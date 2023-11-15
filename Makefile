all: main.o
	@gcc main.o functions.o -o exe -lm
	@rm -r main.o functions.o
functions.o: ./lib/functions.c
	@gcc functions.c -c -Wall
main.o: main.c
	@gcc main.c -c -Wall
run:
	@./exe 