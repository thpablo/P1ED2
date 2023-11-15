all: main.o functions.o
	@gcc main.o functions.o -o exe -lm
	@rm -r main.o functions.o
functions.o: functions.c
	@gcc functions.c -c -Wall
main.o: main.c
	@gcc main.c -c -Wall
run:
	@./exe 