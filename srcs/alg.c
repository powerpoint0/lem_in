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

t_path*        ft_create_path(t_data *map)
{
	t_path *path;
	t_path *new_point;
	t_point *point;

	path = NULL;
	point = map->end;
	while(point)
	{
		if (!(new_point = (t_path *) ft_memalloc(sizeof(t_path))))
			put_err("Init.there is no memory for path");
		if(path)
			path->prev = new_point;
		new_point->next = path;
		new_point->points = point;
		new_point->points->in_path = 2;
		path = new_point;
		if(path->points == map->start)
			break;
		point = point->prev_room_path;
	}
	return (path);
}

t_path**    ft_paths_without_common_edges(t_sline *slines, t_path **paths, int num_paths, t_data *map)
{
	int        i;
//	int        num_paths;

//	i = 0;
//	num_paths = 0;
	ft_init_slines(slines);

//	while(paths[i++])
		num_paths++;

//	i = 0;
//	while(paths[i])      /////////////////////////////
//		paths[i++] = NULL;
	i = 0;
	while (!ft_bellman_ford(map) && i < num_paths)
	{
		paths[i] = ft_create_path(map);
		if(ft_change_edge(map->slines))
		{
			ft_free_paths(paths);
			paths = ft_paths_without_common_edges(map->slines, paths, i, map);
		}
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

//void	ft_copy_in_best_paths_mall(t_path **paths,t_path **best_paths)
//{
//	int		i;
//	t_path	*path_point;
//
//
//	i = 0;
//	while(paths[i])
//	{
//		path_point = paths[i];
//		if(!(best_paths[i] = (t_path *) ft_memalloc(sizeof(t_path))))
//		put_err("Init.there is no memory for path");
//		= path_point->points;
//		i++;
//	}
//	best_paths[0]->num_of_steps_in_paths = paths[0]->num_of_steps_in_paths;
//}
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


void ft_free_path(t_path **path)
{
	t_path *root;
	t_path *tmp;

	root = *path;
	while (root)
	{
		tmp = root;
		root = root->next;
		free(tmp);
	}
	*path = NULL;
}


void ft_free_paths(t_path **paths)
{
	int i;
	t_path *tmp;
	t_path *path_point;

	i = 0;
	if(!paths)
		return;
	while(paths[i])
	{
		ft_free_path(&paths[i]);
		i++;
	}
}

//void ft_free_paths(t_path **paths)
//{
//	int i;
//	t_path *tmp;
//	t_path *path_point;
//
//	i = 0;
//	if(!paths)
//		return;
//	while(paths[i])
//	{
//		path_point = paths[i];
//		while(path_point)
//		{
//			tmp = path_point;
//			path_point = path_point->next;
//			free(tmp);
//		}
//		paths[i] = NULL;
//		i++;
//	}
//}
int		ft_change_paths_for_the_best(t_path **paths,t_path **best_paths, t_data *map)
{
	if(!*best_paths)
	{
		ft_copy_in_best_paths(paths, best_paths);
		return(0);
	}
	paths[0]->num_of_steps_in_paths = iter_count(paths, map);
	best_paths[0]->num_of_steps_in_paths = iter_count(best_paths, map);
	if(paths[0]->num_of_steps_in_paths <=best_paths[0]->num_of_steps_in_paths)
	{
		if (*paths != *best_paths)
			ft_free_paths(best_paths);
		ft_copy_in_best_paths(paths, best_paths);
	}
	else if (paths[0]->num_of_steps_in_paths > best_paths[0]->num_of_steps_in_paths)
		return (-1);
	return(0);
}

void	ft_free_all_in_alg(t_path **paths, t_sline *slines)
{
	t_sline	*prev_slines;

	while (slines)
	{
		prev_slines = slines;
		slines = slines->next;
		free(prev_slines);
	}
	if(paths)
		free(paths);
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
	while(!(check = ft_bellman_ford(map)) && i < map->num_ants)
	{
		paths[i] = ft_create_path(map);
		if (ft_change_edge(map->slines)) {
			ft_free_path(&paths[i]);
			ft_bzero(paths, sizeof(t_path *) * i);
			paths = ft_paths_without_common_edges(map->slines, paths, i, map);
		}
		if (ft_change_paths_for_the_best(paths, best_paths, map))
			break;
		i++;
	}
	if(check < 0 && !*best_paths)
		put_err("ERROR.There is no path between START and END");
	if (*paths != *best_paths)
		ft_free_paths(paths);
	ft_free_all_in_alg(paths,map->slines);
	return (best_paths);
}
	//ft_check_repeat_rooms(best_paths);
//	printf("\nbest paths end %d\n", 0);
//	print_paths(best_paths);
//	printf("\nbest paths end %d\n", 0);


//если есть общие ребра,то удаляем их и заменяем путь снова через БФ
//проверяем ,за сколько шагов пройдет
//находим еще один путь.во второй комплект путей.смотрим,за сколько шагов пройдет
//если с новым путем быстрее,то копируем в лучшие пути
// если медленнее ,выходим из цикла