main: main.o
	gcc -o main main.c 

clean:
	rm *.o

run: main.out
	./main.out
