#include "lem_in.h"

int		ft_find_first(t_data *map)
{
	t_point	*header;

	map->start = NULL;
	header =  map->points;
	while (map->points && !map->start)
	{
		if (map->points->st_end == START)
			map->start = map->points;
		map->points = map->points->next;
	}
	map->points = header;
	return (0);
}

int		ft_find_end(t_data *map)
{
	t_point	*header;

	header =  map->points;
	map->end = NULL;
	while (map->points && !map->end)
	{
		if (map->points->st_end == END)
			map->end = map->points;
		map->points = map->points->next;
	}
	map->points = header;
	return (0);
}

//t_point	*ft_find_next(t_data *map, t_path *path)
//{
//	t_point *next;
//	int		num;
//
//	num = -1;
//	next = NULL;
//	while (map->lines && num < 0)
//	{
//		if (path->point->num == map->lines->num_first || path->point->num == map->lines->num_next )
//			num = (path->point->num == map->lines->num_first)? map->lines->num_next : map->lines->num_first;
//		else
//		map->lines = map->lines->next;
//	}
//	while (map->points && !next)
//	{
//		if (map->points->num == num)
//			next = map->points;
//		map->points = map->points->next;
//	}
//	map->lines = map->header_lines;
//	map->points = map->header_points;
//	return(next);
//}

int		ft_letGoAnts(t_path **paths)
{

}

int		ft_find_smallest_way(t_data *map)   //poisk kratchaishego puti bez malloca c сохранием обратных указателей
{

	return(1);
}

t_path	*ft_new_path(t_data *map)				//vosstanovlenie puti po ukazatelyam
{
	t_path *path;
	t_point *room;

	while(map->end->prev_room != map->start)
	{
		if(!path)
		{
			if (!(path = (t_path*)ft_memalloc(sizeof(t_path))))
				put_err("Init.path hasn't created .path not found");
			path->last_points = map->end;
			path->points = map->end;
			path->points->next = NULL;
 		}
	 	else
		{

			//malloc point
			//path->points
			//dobavlyaem komnaty v spisok ot enda k startu
			//otkluchaem komnayy
		}
	 }
	 return(path);
}

int	alg(t_data *map)
{
	t_path **paths;
	int i;
	i = 0;

	if (!(paths = (t_path **) ft_memalloc(sizeof(t_path *) * 2)))
		put_err("Init.there is no memory for paths");
	ft_find_first(map);
	ft_find_end(map);
	while (ft_find_smallest_way(map))
	{
		paths[i] = ft_new_path(map);
		i++;
	}
	ft_letGoAnts(paths);
	return (0);
}
//	t_point	*header;
//	header = map->points;
//	if (!map->points)
//	{
//		map->points = new_point(str, mod_command);
//	}
//	else
//	{
//		while (map->points->next != NULL)
//			map->points = map->points->next;
//		map->points->next = new_point(str, mod_command);
//		map->points = header;
//	}



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
