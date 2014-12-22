build: snake

snake: tema2.c
	gcc -Wall tema2.c -o snake -lncurses


run:
	./snake

clean:
	rm -f snake
