#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "nqueue/queue.h"
#include "parser.h"


int main(int argc, char* argv[]) {
	double exec_time;
	double max_value;
	city_details city_info;

	if (argc != 3) {
		raise_error("Error: input should be in format 'tsp <cities file> <max value>'.");
	}

	sscanf(argv[2], "%lf", &max_value);
	city_info = parse_cities_file(argv[1]); 

	exec_time = -omp_get_wtime();
	
	print_city_info(city_info);
	free_city_info(city_info);


//	tsp();

	exec_time += omp_get_wtime();
	fprintf(stderr, "%.1fs\n", exec_time);

//	print_result();

}