#include "lem_in.h"

#define CLOSE 1

//void ft_change_edge(t_path *path, t_data *map)
//{
//	int i = 0;
//
//	while (path->points->arr_lines[i] != path->next->points)
//		i++;
//	//path->points->check[i + 1] = (path->points->check[i + 1] == 1) ? -1 : 0;
//	path->points->check[i + 1] = 0;
//}

void ft_change_edge(t_path *path, t_sline *slines, t_point *end)
{
	t_sline *header;
	t_point *tmp;

	header = slines;
	while(slines)
	{
//		if(!slines->out->in_path)
		//slines->out->prev_room_path = NULL;
		if(slines->out->in_path && slines->in->in_path && slines->out->prev_room_path == slines->in)
		{
			tmp = slines->in;
			slines->in = slines->out;
			slines->out = tmp;
			if (slines->weight == -1)
				slines->close= CLOSE;
			slines->weight *= -1;
		}
		slines = slines->next;
	}
	slines = header;
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
			path->len = map->end->cost;
		}
		else
		{
//			if (path->points->name,path->points->prev_room_path->name)
//			{
//				path->points->prev_room_path->in_path =2;
//
//			}
			if (!(new_point = (t_path *) ft_memalloc(sizeof(t_path))))
				put_err("Init.there is no memory for path");
			path->prev = new_point;
			new_point->next = path;
			if(path->points->prev_room_path)
				new_point->points = path->points->prev_room_path;
			else
				new_point->points = map->start;
			new_point->last_points = path->last_points;
			new_point->len = map->end->cost;
			path = new_point;
			path->points->in_path =2;
			if(path->points == map->start)
				break;
		}
	}
	return (path);
}


void print_paths(t_path **paths)
{
	t_path *path;
	int i;

	i = 0;

	while (paths[i])
	{
		path = paths[i];
		while (path)
		{
			printf("%s%d ", path->points->name,  path->points->p);
			path = path->next;
		}
		printf("\n");
		i++;
	}
}

int	alg(t_data *map)
{
	t_path **paths;
	int check;
	int i;

	i = 0;
	if (!(paths = (t_path **)ft_memalloc(sizeof(t_path *) * (map->start->check[0] + 1))))
		put_err("ERROR.Init.there is no memory for paths");
	while (!(check = ft_bellman_ford(map)))
	{
		paths[i] = ft_create_path(paths[i], map);
		ft_change_edge(paths[i], map->slines, map->end);
		//если есть общие ребра,то удаляем их и заменяем путь снова через БФ
		//проверяем ,за сколько шагов пройдет
		//находим еще один путь.во второй комплект путей.смотрим,за сколько шагов пройдет
		//если с новым путем быстрее,то добавляем путь
		// если медленнее ,выходим из цикла
		i++;
		//print_sline(map);
	}
	if(check < 0 && !*paths)
		put_err("ERROR.There is no path between START and END");
	print_paths(paths);
	ft_letGoAnts(paths, map);
	return (0);
}