all: object compile

object:
	mkdir -p objects
	gcc -g -c main.c source/*.c -Iheaders && mv *.o objects/

compile:
	gcc -o trab2 objects/*.o -lm

run:
	./trab2 in-exemplos/3.txt 5 saida.txt

valgrind:
	valgrind ./trab2 in-exemplos/3.txt 5 saida.txt

clean:
	rm -r trab2 objects