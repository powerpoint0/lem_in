#include <stdio.h>
#include "lem-in.h"
#include <fcntl.h>
#include <stdlib.h>

void	free_all(t_data	*map)
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
}
int		put_err(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

int 	main(int argc, char **argv)
{
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
	map = read_map(fd);
	best_paths = ft_alg(map);
	ft_letGoAnts(best_paths, map);
	free_all(map);
	return(0);
}
