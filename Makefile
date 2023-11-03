all: main.o fileGenerator.o
	@gcc main.o fileGenerator.o -o exe -lm
	@rm -r main.o
	@rm -r fileGenerator.o
main.o: main.c
	@gcc main.c -c -Wall
fileGenerator.o: fileGenerator.c
	@gcc fileGenerator.c -c -Wall
run:
	@./exe 
