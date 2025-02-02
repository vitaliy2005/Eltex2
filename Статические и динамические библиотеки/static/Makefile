all:
	gcc -c calc.c -o calc.o
	gcc -c io.c -o io.o
	gcc -c helper.c -o helper.o
	ar rcs libapp.a calc.o io.o helper.o
	gcc main.c -L. -lapp -o main
