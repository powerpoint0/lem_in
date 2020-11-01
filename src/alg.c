#include "lem_in.h"

int	ft_change_edge(t_path *path, t_sline *slines, t_point *end)
{
	t_sline *header;
	t_point *tmp;
	int		common_edges;

	if(!slines->tmp_in)                    //////////////////попросить Юру добавить при инициализации
		slines->tmp_in = slines->in;   /////////
	header = slines;
	while(slines)
	{
		if(slines->out->in_path && slines->in->in_path && slines->out->prev_room_path == slines->in)
		{
			tmp = slines->in;
			slines->in = slines->out;
			slines->out = tmp;
			if (slines->weight == -1)
			{
				slines->close = CLOSE;
				common_edges = 1;
			}
			slines->weight *= -1;
		}
		slines = slines->next;
	}
	slines = header;
	return(common_edges);
}

t_path*		ft_create_path(t_path *path, t_data *map)
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

t_path**	ft_paths_without_common_edges(t_sline *slines,t_path **paths, t_data *map)
{
	ft_init_slines(slines);
	ft_init_points(map);
	//обнуляем все данные в ребрах и комнатах, кроме отметок клоз
	//запуск БФ с условием:если слозе,то пропуск ребра
	//собираем пути на место прежнего патс,изменяя данные
	//стираем первые пути
}

int	ft_num_of_steps(t_path **paths)   //////позже заменить на кол-во шагов от Юры
{
	int i;
	int num;

	num = 0;
	i = 0;
	while(paths[i])
	{
		num += paths[i]->len;
		i++;
	}
	return(num);
}

void	ft_copy_in_best_paths(t_path **paths,t_path **best_paths)
{
	int i;

	i = 0;
	while(paths[i])
	{
		best_paths[i] = paths[i];
		i++;
	}
}

int ft_change_paths_for_the_best(t_path **paths,t_path **best_paths)
{
	t_path **tmp;
	if(!best_paths)
	{
		ft_copy_in_best_paths(paths, best_paths);
		return 0;
	}
	paths[0]->num_of_steps_for_all_paths = ft_num_of_steps(paths);
	if(paths[0]->num_of_steps_for_all_paths < best_paths[0]->num_of_steps_for_all_paths)
	{
		tmp = best_paths;
		ft_copy_in_best_paths(paths, best_paths); //ft best_paths = paths;
		//ft_free_paths(tmp);
	}
	else if (paths[0]->num_of_steps_for_all_paths > best_paths[0]->num_of_steps_for_all_paths)
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
	if (!(paths = (t_path **)ft_memalloc(sizeof(t_path *) * (map->start->check[0] + 1))))
		put_err("ERROR.Init.there is no memory for paths");
	if (!(best_paths = (t_path **)ft_memalloc(sizeof(t_path *) * (map->start->check[0] + 1))))
		put_err("ERROR.Init.there is no memory for paths");
	while(!(check = ft_bellman_ford(map)))
	{
		paths[i] = ft_create_path(paths[i], map);
		if(ft_change_edge(paths[i], map->slines, map->end))
			paths = ft_paths_without_common_edges(map->slines, paths, map);
		if(ft_change_paths_for_the_best(paths, best_paths))
			break;
		i++;
		//print_sline(map);
	}
	if(check < 0 && !*paths)
		put_err("ERROR.There is no path between START and END");
	print_paths(paths);
	return (best_paths);
}

//если есть общие ребра,то удаляем их и заменяем путь снова через БФ
//проверяем ,за сколько шагов пройдет
//находим еще один путь.во второй комплект путей.смотрим,за сколько шагов пройдет
//если с новым путем быстрее,то добавляем путь
// если медленнее ,выходим из цикла