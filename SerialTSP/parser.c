#include "parser.h"
#include <stdlib.h>
#include <stdio.h>


void raise_error(char msg[]) {
	fprintf(stderr, "%s", msg);
	exit(1);
}

/* Reads the cities file and returns its information within a struct */
city_details parse_cities_file(char* cities_file_path) {
	city_details city_info;

	FILE* cities_file = fopen(cities_file_path, "r");
	if (cities_file == NULL) {
		raise_error("Error: file does not exist.");
	}

	// Stores number of cities and number of direct connections between them
	fscanf(cities_file, "%d %d\n", &city_info.nr_cities, &city_info.nr_conns);

	city_info.dist_matrix = init_dist_matrix(city_info.nr_cities);

	// Stores distances between each directly connected city
	for (int i = 0; i < city_info.nr_conns; i++) {
		int city1, city2;
		double dist;

		fscanf(cities_file, "%d %d %lf\n", &city1, &city2, &dist);
		city_info.dist_matrix[city1][city2] = city_info.dist_matrix[city2][city1] = dist;
	}

	fclose(cities_file);
    //print_city_info(city_info);

	return city_info;
}


/* Initializes distance matrix, with each city unreachable from each other */
double** init_dist_matrix(int nr_cities) {
	double** dist_matrix = (double**) malloc(sizeof(double) * nr_cities);

	for (int i = 0; i < nr_cities; i++) {
		double* city_conns = (double*) malloc(sizeof(double) * nr_cities);
		
		for (int j = 0; j < nr_cities; j++)
			city_conns[j] = -1.00;

		dist_matrix[i] = city_conns;
	}

	return dist_matrix;
}

/* Prints number of cities, number of direct connections, and distances matrix */
void print_city_info(city_details city_info) {
	printf("PRINTING CITIES INFO:\n");
	printf("Nr cities = %d. Nr conns = %d.\n", city_info.nr_cities, city_info.nr_conns);

	printf("Conns:\n");
	for (int i = 0; i < city_info.nr_cities; i++) {
		for (int j = 0; j < city_info.nr_cities; j++)
			printf("%0.2f\t", city_info.dist_matrix[i][j]);

		printf("\n");
	}
	printf("\n");
}