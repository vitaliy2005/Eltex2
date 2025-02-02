all:
	gcc -c -fPIC calc.c -o calc.o
	gcc -c -fPIC io.c -o io.o
	gcc -c -fPIC helper.c -o helper.o
	gcc -shared -o libapp.so calc.o io.o helper.o
	gcc main.c -L. -lapp -Wl,-rpath,. -o main
