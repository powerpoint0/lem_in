#include "lem_in.h"

t_point	*find_first(t_data *map)
{
	t_point	*first;
	t_point	*header;

	first = NULL;
	header =  map->points;
	while(map->points && !first)
	{
		if (map->points->st_end == START)
			first = map->points;
		map->points = map->points->next;
	}
	map->points = header;
	return (first);
}
/*
t_point	*find_next(t_data *map)
{
	t_point	*point_header;
	t_line	*line_header;

	point_header = map->points;
	line_header = map->lines;
	while(map->lines)
	{
		if ()
	}
}
*/

int	alg(t_data *map)
{
	t_path	*path;

	if (!(path = (t_path*)ft_memalloc(sizeof(t_path))))
		put_err("Init.Not creat path");
	path->point = find_first(map);

	return (0);
}