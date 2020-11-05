#include "lem-in.h"

int	ft_change_edge(t_sline *slines)
{
	t_point *tmp;
	int		common_edges;

	common_edges = 0;
	while(slines)
	{
		if(slines->out->in_path && slines->in->in_path
		&& slines->out->prev_room_path == slines->in && slines->close != CLOSE)
		{
			if (slines->weight == -1)
			{
				slines->close = CLOSE;
				common_edges = 1;
			}
			tmp = slines->in;
			slines->in = slines->out;
			slines->out = tmp;
			slines->weight *= -1;
		}
		slines = slines->next;
	}
	return(common_edges);
}

t_path*		ft_create_path(t_path *path, t_data *map)
{
	t_path *new_point;

	if (!path)
	{
		if (!(path = (t_path *) ft_memalloc(sizeof(t_path))))
			put_err("Init.there is no memory for path");
		path->points = map->end;
		path->last_points = map->end;
		path->len = map->end->cost;
		path->points->in_path = 2;
	}
	while(map->start)
	{
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
	return (path);
}

t_path**	ft_paths_without_common_edges(t_sline *slines, t_path **paths, t_data *map)
{
	int		i;
	int		num_paths;

	i = 0;
	//ft_free_paths
	ft_init_slines(slines);
	while(paths[i])	////////free(paths) vse puti
		paths[i++] = NULL;
	num_paths = i;
	i = 0;
	while (!ft_bellman_ford(map) && i < num_paths)
	{
		paths[i] = ft_create_path(paths[i], map);
		if(ft_change_edge(map->slines))
			paths = ft_paths_without_common_edges(map->slines, paths, map);
		i++;
	}
	return (paths);
}
//обнуляем все данные в ребрах и комнатах, кроме отметок клоз
//запуск БФ с условием:если слозе,то пропуск ребра
//собираем пути на место прежнего патс,изменяя данные
//стираем первые пути
void	ft_copy_in_best_paths(t_path **paths,t_path **best_paths)
{
	int i;

	i = 0;
	while(paths[i])
	{
		best_paths[i] = paths[i];
		i++;
	}
	best_paths[0]->num_of_steps_in_paths = paths[0]->num_of_steps_in_paths;
}

int		ft_how_much_edges(t_sline *slines)
{
	int i;

	i = 0;
	while(slines)
	{
		i++;
		slines = slines->next;
	}
	return(i);
}

void ft_free_paths(t_path **paths)
{
	int i;

	i = 0;
	while(paths[i])
	{
		while(paths[i]->next)
		{
			//pa
		}
		i++;
	}
}

int			ft_change_paths_for_the_best(t_path **paths,t_path **best_paths, t_data *map)
{
	if(!*best_paths)
	{
		ft_copy_in_best_paths(paths, best_paths);
		return(0);
	}
	paths[0]->num_of_steps_in_paths = iter_count(paths, map);
	best_paths[0]->num_of_steps_in_paths = iter_count(best_paths, map);
	if(paths[0]->num_of_steps_in_paths <=best_paths[0]->num_of_steps_in_paths)  //////чем меньшее колво шагов требуется муравьям
	{
		//ft_free_paths(best_paths); (чистим,удаляя пути все,не удаляя массив,заполняем нулями)
		ft_copy_in_best_paths(paths, best_paths); //ft best_paths = paths;
	}
	else if (paths[0]->num_of_steps_in_paths > best_paths[0]->num_of_steps_in_paths)
	{
		//ft_free_paths(paths);
		return(-1);
	}
	return(0);
}

t_path	**ft_alg(t_data *map)
{
	t_path	**paths;
	t_path	**best_paths;
	int		check;
	int		i;

	i = 0;
	ft_num_of_max_paths(map);
	paths = ft_init_paths(map);
	best_paths = ft_init_paths(map);
	map->num_of_edges = ft_how_much_edges(map->slines); ///////perekinut v read.c
	while(!(check = ft_bellman_ford(map)))
	{
		paths[i] = ft_create_path(paths[i], map);
		if (ft_change_edge(map->slines))
			paths = ft_paths_without_common_edges(map->slines, paths, map);
		if (ft_change_paths_for_the_best(paths, best_paths, map))
			break;
		i++;
	}
	if(check < 0 && !*best_paths)
		put_err("ERROR.There is no path between START and END");
	//ft_check_repeat_rooms(best_paths);
//	printf("\nbest paths end %d\n", 0);
//	print_paths(best_paths);
//	printf("\nbest paths end %d\n", 0);
	return (best_paths);
}

//если есть общие ребра,то удаляем их и заменяем путь снова через БФ
//проверяем ,за сколько шагов пройдет
//находим еще один путь.во второй комплект путей.смотрим,за сколько шагов пройдет
//если с новым путем быстрее,то добавляем путь
// если медленнее ,выходим из цикла