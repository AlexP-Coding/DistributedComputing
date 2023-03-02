# valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --show-below-main=yes ./istserver
# valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --show-below-main=yes ./istclient
CFLAGS =-Wall -Wextra -ansi -pedantic -fsanitize=address -std=gnu99 -ggdb3 -g
CPDFLAGS = -O3 -fopenmp
CPDEXTRA = $(CPDFLAGS) -Wall -Wextra -ansi -pedantic -fsanitize=address -std=gnu99 -ggdb3 -g

all: tsp.c parser.c
	gcc $(CPDFLAGS) tsp.c parser.c -o tsp

extra: tsp.c parser.c
	gcc $(CPDEXTRA) tsp.c parser.c -o tsp

clean:
	rm tsp