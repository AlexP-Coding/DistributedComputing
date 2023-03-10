# valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --show-below-main=yes ./tsp pub-instances/teste1.in 40
CPDFLAGS = -O3 -fopenmp -std=c++11
EXTRA = -Wall -Wextra -ansi -pedantic -fsanitize=address
CPDEXTRA = $(CPDFLAGS) $(EXTRA)
TRAVASSOS = -O3 -std=c++11
TRAVASSOSEXTRA = $(TRAVASSOS) $(EXTRA)

all: tsp.cpp
	g++ $(CPDFLAGS) -g tsp.cpp -o tsp

extra: tsp.cpp
	g++ $(CPDEXTRA) -g tsp.cpp -o tsp

travassos: tsp.cpp
	g++ $(TRAVASSOS) -g tsp.cpp -o tsp

travassos_extra: tsp.cpp
	g++ $(TRAVASSOSEXTRA) -g tsp.cpp -o tsp

clean:
	rm tsp

redo: clean all 

redo_extra: clean extra
