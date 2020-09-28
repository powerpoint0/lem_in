#include "lem_in.h"

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

int		ft_letGoAnts(int **paths)
{
	return(0);
}

int ft_find_way(t_data *map)
{
	int len;
	len = 0;

	return(len);
}

int		ft_find_smallest_way(t_data *map)   //poisk kratchaishego puti bez malloca c сохранием обратных указателей
{
	int len1;
	int len2;

	len1 = 0;
	len2 = 0;
	while((len2 = ft_find_way(map)) > 1)
	{
		if(len1 < len2)
		{
			//zatiraem prev put'
			len1 = len2;
		}
	}
	return(len1);
}

int		*ft_new_path(t_data *map)				//vosstanovlenie puti po ukazatelyam
{
	int *path;
	int len;
	t_point *header;
	t_point *next;
	len = 2;

	next = NULL;
	header = map->points;
	map->points = map->end;
	while (map->points->prev_room_path != map->start)
	{
		len++;
		map->points = map->points->prev_room_path;
	}
	if (!(path = (int*)ft_memalloc(sizeof(int)* (len+1))))
		put_err("Init.path hasn't created .path not found");
	map->points = map->end;
	path[0] = len;
	path[len] = map->end->num;
	while(len)
	{
		path[len] = map->points->prev_room_path->num;
		next = map->points->prev_room_path;
		map->points->prev_room_path = NULL;   //zatiraem put'
		if(!map->points->st_end)
			map->points->close = 1;       //otkluchaem komnayy
		map->points = next;
		len--;
	}
	map->points = header;
	return(path);
}

int	alg(t_data *map)
{
	int **paths;
	int i;
	i = 0;

	if (!(paths = (int **)ft_memalloc(sizeof(int *) * 20)))
		put_err("Init.there is no memory for paths");
	while (ft_find_smallest_way(map))
	{
		//if(!paths[i])
			//perekopirovat massiv i dobavit strok
			//free proshlyi massiv
		paths[i] = ft_new_path(map);
		i++;
	}
	ft_letGoAnts(paths);
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
