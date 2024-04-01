all: object compile

object:
	mkdir -p objects
	gcc -c main.c source/*.c -Iheaders && mv *.o objects/

compile:
	gcc -o exec objects/*.o -lm

run:
	./exec in-exemplos/1.txt 3 saida.txt

valgrind:
	valgrind ./exec in-exemplos/1.txt 3 saida.txt

clean:
	rm exec objects/* 

