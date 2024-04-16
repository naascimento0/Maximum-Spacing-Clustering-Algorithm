all: object compile

object:
	mkdir -p objects
	gcc -g -c main.c source/*.c source/data_structures/*.c -Iheaders && mv *.o objects/

compile:
	gcc -o trab1 objects/*.o -lm

run:
	./trab1 in-exemplos/6.txt 3 saida.txt

valgrind:
	valgrind ./trab1 in-exemplos/6.txt 3 saida.txt

clean:
	rm trab1 objects/* 

