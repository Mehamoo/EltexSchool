binary: main.o libexp34s.a
	gcc main.o -L. -lexp34s -o main
main.o: main.c
	gcc -c main.c
libexp34s.a: exp3.o exp4.o
	ar cr libexp34s.a exp3.o exp4.o
exp3.o: exp3.c
	gcc -c exp3.c
exp4.o: exp4.c
	gcc -c exp4.c
clean:
	rm -f *.o *.a main
