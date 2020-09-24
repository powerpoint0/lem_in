#include "lem_in.h"

t_point	*find_first(t_data *map)
{
	t_point	*first;
	t_point	*header;

	first = NULL;
	header =  map->points;
	while (map->points && !first)
	{
		if (map->points->st_end == START)
			first = map->points;
		map->points = map->points->next;
	}
	map->points = header;
	return (first);
}

t_point	*ft_find_next(t_data *map, t_path *path)
{
	t_point *next;
	int		num;

	num = -1;
	next = NULL;
	while (map->lines && num < 0)
	{
		if (path->point->num == map->lines->num_first || path->point->num == map->lines->num_next )
			num = (path->point->num == map->lines->num_first)? map->lines->num_next : map->lines->num_first;
		else
		map->lines = map->lines->next;
	}
	while (map->points && !next)
	{
		if (map->points->num == num)
			next = map->points;
		map->points = map->points->next;
	}
	map->lines = map->header_lines;
	map->points = map->header_points;
	return(next);
}

int	alg(t_data *map)
{
	t_path  **array_path;
	t_path	*path;
	int i;
	i = 1;

	map->header_lines = map->lines;
	map->header_points = map->points;
	if (!(array_path = (t_path**)ft_memalloc(sizeof(t_path*) * 2)))
		put_err("Init.there is no memory for paths");
	if (!(path = (t_path*)ft_memalloc(sizeof(t_path))))
		put_err("Init.path hasn't created .path not found");
	array_path[i] = path;
	path->point = find_first(map);
	path->point->next = NULL;
	path->len++;
	path->point->next = ft_find_next(map, path);
	path->point = path->point->next;
	path->point->next = NULL;

	return (0);
}
//macсив указателей на пути
//цикл:пока не енд
//обход в ширину
//// обход в глубину для каждой точки
//запись всех путей в массив путей
//если путь не ведет к энду,вычеркнуть из путей
//посчитать длину пути

//распределение муравьев по формуле

//цикл:пока не все муравьи в энде
//проход муравьев с выводом
