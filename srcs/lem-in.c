#include "lem-in.h"

void	free_all(t_data	*map, t_path **best_paths)
{
	t_point	*prev_points;
	t_line	*prev_lines;

	while (map && map->points)
	{
		prev_points = map->points;
		map->points = map->points->next;
		free(prev_points);
	}
	while (map && map->lines)
	{
		prev_lines = map->lines;
		map->lines = map->lines->next;
		free(prev_lines);
	}
	if (map)
		free(map);
	ft_free_paths(best_paths);
	if(best_paths)
		free(best_paths);
}

int		put_err(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

int 	main(int argc, char **argv)
{
	clock_t all_1 = clock();
	int		fd;
	t_data	*map;
	t_path **best_paths;

	map = NULL;
	best_paths = NULL;
	if (argc < 2)
		put_err("Error");
	fd = (ft_strequ(argv[1], "<")) ? open(argv[2], O_RDONLY) : open(argv[1], O_RDONLY);
	if (fd < 0)
		put_err("Not open file");
	clock_t r_1 = clock();
	map = read_map(fd);
		clock_t r_2 = clock();
		double r_diff = (double) (r_2 - r_1)/CLOCKS_PER_SEC;

		clock_t a_1 = clock();
	best_paths = ft_alg(map);
		clock_t a_2 = clock();
		double a_diff = (double) (a_2 - a_1)/CLOCKS_PER_SEC;

	clock_t go_1 = clock();
	ft_letGoAnts(best_paths, map);
	clock_t go_2 = clock();
	double go_diff = (double) (go_2 - go_1)/CLOCKS_PER_SEC;
	free_all(map, best_paths);
	clock_t all_2 = clock();
	double all_diff = (double) (all_2 - all_1)/CLOCKS_PER_SEC;
	printf("Read time = %f\n", r_diff);
	printf("Algo time = %f\n", a_diff);
	printf("Go time = %f\n", go_diff);
	printf("All time = %f\n", all_diff);
	return(0);
}
