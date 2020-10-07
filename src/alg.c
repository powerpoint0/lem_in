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

int		ft_letGoAnts(t_path **paths)
{
	return(0);
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


int ft_find_way(t_data *map)     // BFS
{
	int len;
	t_point *current;
	len = 1;
	//ft_bfs(map);
//	current = map->start;
//	while(current != map->end)
//	{
//		if()
//	}
	return(len);
}

void	ft_delete_way(t_data *map)
{
	t_point *next;
	t_point *header;

	header = map->points;
	next = NULL;
	map->points = map->end;
	while(map->points->prev_room_path != map->start)
	{
		next = map->points->prev_room_path;
		map->points->prev_room_path = NULL;   //zatiraem put'
		if(!map->points->st_end)
			map->points->close = 0;       //vkluchaem komnayy
		map->points = next;
	}
	map->points = header;
}

int		ft_find_smallest_way(t_data *map)   //poisk kratchaishego puti bez malloca c сохранием обратных указателей
{
	int len1;
	int len2;
	int	*path;

	len1 = 0;
	len2 = 0;
	len1 = ft_find_way(map);
	if (len1 == 0)
		return(0);
	path = ft_new_path(map);
	while((len2 = ft_find_way(map)) > 1)
	{
		if(len1 > len2)
		{
			free(path);
			path = ft_new_path(map);
			len1 = len2;
		}
		else
			ft_delete_way(map);		//zatiraem prev put'
	}
	return(len1);
}


void	ft_free_int(int **copy)
{
	int j;
	int str;

	if(!copy)
		return;
	str = copy[0][1];
	j = 0;
	while(j <= str)
	{
		free(copy[j]);
		j++;
	}
	free(copy);
}

int		**ft_realloc(int **paths, int str)
{
	int	**copy;
	int j;

	j = 0;
	copy = paths;
	if (!(paths = (int **)ft_memalloc(sizeof(int *) * str)))
		put_err("Init.there is no memory for paths");
	while(j <= copy[0][1])
	{
		ft_memcpy(paths[j], copy[j], sizeof(int)* (copy[j][0]+1));
		j++;
	}
	ft_free_int(copy);
	return(paths);
}

t_path *		ft_create_path(t_path *path, t_data *map)
{
	t_path *new_point;

	while(map->start)
	{
		if (!path)
		{
			if (!(path = (t_path *) ft_memalloc(sizeof(t_path))))
				put_err("Init.there is no memory for path");
			path->points = map->end;
			path->last_points = map->end;
			path->len = map->end->bfs_level;
		}
		else
		{
			if (!(new_point = (t_path *) ft_memalloc(sizeof(t_path))))
				put_err("Init.there is no memory for path");
			new_point->next = path;
			if(path->points->prev_room_path)
				new_point->points = path->points->prev_room_path;
			else
				new_point->points = map->start;
			new_point->last_points = path->last_points;
			new_point->len = map->end->bfs_level;
			path = new_point;
			if(path->points == map->start)
				break;
			path->points->close = 2;
		}
	}
	return (path);
}

int	alg(t_data *map)
{
	t_path **paths;
	int check;
	int i;
	int strings;

	strings = 21;
	i = 0;
	if (!(paths = (t_path **)ft_memalloc(sizeof(t_path *) * strings)))
		put_err("ERROR.Init.there is no memory for paths");
	//printf("end %d\n",map->end->bfs_level);

	while (!(check = ft_bfs(map)))
	{
//		if(i >= strings)
//		{
//			strings += 10;
//			paths = ft_realloc(paths, strings);
//		}
		paths[i] = ft_create_path(paths[i], map);
		i++;
	}
	if(check < 0 && !*paths)
		put_err("ERROR.There is no path between START and END");
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