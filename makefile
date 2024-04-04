all: object compile

object:
	mkdir -p objects
	gcc -c main.c source/*.c -Iheaders && mv *.o objects/

compile:
	gcc -o trab1 objects/*.o -lm

run:
	./trab1 in-exemplos/1.txt 3 saida.txt

valgrind:
	valgrind ./trab1 in-exemplos/1.txt 3 saida.txt

clean:
	rm trab1 objects/* 

