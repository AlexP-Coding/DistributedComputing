/* Contains details on the cities and their direct connections */
typedef struct city_details {
    int nr_cities;
    int nr_conns;
    double** dist_matrix;
} city_details;

void raise_error(char *msg);

city_details parse_cities_file(char* cities_file_path);

void free_city_info(city_details city_info);

double** init_dist_matrix(int nr_cities);

void print_city_info(city_details city_info);