all: main.o fileGenarator.o
	@gcc main.o fileGenarator.o -o exe -lm
	@rm -r main.o
	@rm -r fileGenarator.o
main.o: main.c
	@gcc main.c -c -Wall
fileGenarator.o: fileGenarator.c
	@gcc fileGenarator.c -c -Wall
run:
	@./exe