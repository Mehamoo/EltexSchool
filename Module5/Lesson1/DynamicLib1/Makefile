main: main.o libexp34dyn.so
	gcc main.o libexp34dyn.so -o main -Wl,-rpath,.
main.o: main.c
	gcc -c main.c
libexp34dyn.so: exp3.o exp4.o
	gcc -shared -o libexp34dyn.so exp3.o exp4.o
exp3.o: exp3.c
	gcc -c -fPIC exp3.c
exp4.o: exp4.c
	gcc -c -fPIC exp4.c
clean:
	rm -f *.o *.so main
