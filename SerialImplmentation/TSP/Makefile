# valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --show-below-main=yes ./istserver
# valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --show-below-main=yes ./istclient
CFLAGS =-Wall -Wextra -ansi -pedantic -fsanitize=address -std=gnu99 -ggdb3 -g
CPDFLAGS = -O3 -fopenmp
CPDEXTRA = $(CPDFLAGS) -Wall -Wextra -ansi -pedantic -fsanitize=address -std=gnu99 -ggdb3 -g

all: tsp.cpp
	g++ $(CPDFLAGS) tsp.cpp -o tsp

extra: tsp.cpp city.cpp
	g++ $(CPDEXTRA) tsp.cpp city.cpp -o tsp

clean:
	rm tsp

redo: clean all 

redo_extra: clean extra
