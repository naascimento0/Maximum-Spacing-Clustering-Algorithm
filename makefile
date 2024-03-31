all: object compile

object:
	gcc -c main.c source/*.c headers/*.h && mv *.o objects/

compile:
	gcc -o exec objects/*.o

run:
	./exec in-exemplos/1.txt 3 saida.txt

valgrind:
	valgrind ./exec in-exemplos/1.txt 3 saida.txt

clean:
	rm exec objects/* 

