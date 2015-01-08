run: snake
	./snake

snake: tema2.c
	gcc -Wall tema2.c -o snake -lncurses -lm

clean:
	rm -f snake
