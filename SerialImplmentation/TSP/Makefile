# valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --show-below-main=yes --verbose ./tsp pub-instances/teste1.in 40
CPDFLAGS = -std=c++11 -O3 -fopenmp
EXTRA = -Wall -Wextra -ansi -pedantic -fsanitize=address
CPDEXTRA = $(CPDFLAGS) $(EXTRA)
TRAVASSOS = -std=c++11 -O3
TRAVASSOSEXTRA = $(TRAVASSOS) $(EXTRA)

all: tsp.cpp
	g++ $(CPDFLAGS) -g tsp.cpp -o tsp

v2: tsp.cpp
	g++ $(CPDFLAGS) -g tsp.cpp -o tsp2

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
