#include "lem_in.h"

int	ft_change_edge(t_path *path, t_sline *slines, t_point *end, t_data *map)
{
	t_sline *header;
	t_point *tmp;
	int		common_edges;

	header = slines;
	common_edges = 0;
	printf("\nbefore change edge%d\n", 0);
	print_sline(map);
	while(slines)
	{
		if(!slines->tmp_in)                    //////////////////попросить Юру добавить при инициализации
			slines->tmp_in = slines->in;   /////////
		if(slines->out->in_path && slines->in->in_path && slines->out->prev_room_path == slines->in && slines->close != CLOSE)
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
	printf("\nafter %d\n", 0);
	print_sline(map);
	slines = header;
	//printf("\n%d\n", common_edges);
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
			path->points->in_path = 2;
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

t_path**	ft_paths_without_common_edges(t_sline *slines, t_path **paths, t_data *map, int num_of_edges)
{
	int		check;
	int		i;
	t_path **last_path;

	i = 0;
	check = 0;
	last_path = paths;
	//best_slines = ft_copy_slines(slines);
	ft_init_slines(slines);
	//ft_init_points(map);

	//print_sline(map);
	////////free(paths) vse puti
	while(paths[i])
		paths[i++] = NULL;
	i = 0;
	while (!(check = ft_bellman_ford(map, num_of_edges)))
	{
		paths[i] = ft_create_path(paths[i], map);
		ft_change_edge(paths[i], map->slines, map->end, map);
		print_paths(paths);
		//ft_free_path(last_path);
		i++;
	}
	return (paths);
	//обнуляем все данные в ребрах и комнатах, кроме отметок клоз
	//запуск БФ с условием:если слозе,то пропуск ребра
	//собираем пути на место прежнего патс,изменяя данные
	//стираем первые пути
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
	best_paths[0]->num_of_steps_in_paths = paths[0]->num_of_steps_in_paths;
}

int			ft_change_paths_for_the_best(t_path **paths,t_path **best_paths)
{
	if(!*best_paths)
	{
		ft_copy_in_best_paths(paths, best_paths);
		return(0);
	}

//	printf("\n%d\n", paths[0]->num_of_steps_in_paths);
//	printf("\n%d\n", best_paths[0]->num_of_steps_in_paths);
	if(paths[0]->num_of_steps_in_paths < best_paths[0]->num_of_steps_in_paths)  //////чем меньшее колво шагов требуется муравьям
	{
		//ft_free_paths(best_paths); (чистим,удаляя пути все,не удаляя массив,заполняем нулями)
		ft_copy_in_best_paths(paths, best_paths); //ft best_paths = paths;
	}
	else if (paths[0]->num_of_steps_in_paths >= best_paths[0]->num_of_steps_in_paths)
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
	int num_of_edges;

	i = 0;
	if (!(paths = (t_path **)ft_memalloc(sizeof(t_path *) * (map->start->check[0] + 1))))
		put_err("ERROR.Init.there is no memory for paths");
	if (!(best_paths = (t_path **)ft_memalloc(sizeof(t_path *) * (map->start->check[0] + 1))))
		put_err("ERROR.Init.there is no memory for paths");
	num_of_edges = ft_how_much_edges(map->slines);
	while(!(check = ft_bellman_ford(map, num_of_edges)))
	{
		paths[i] = ft_create_path(paths[i], map);
		paths[0]->num_of_steps_in_paths = iter_count(paths, map);
//		print_paths(paths);
//		print_sline(map);
		printf("\n paths %d\n", 0);
		print_paths(paths);
		if(ft_change_edge(paths[i], map->slines, map->end, map))
		{
			printf("\nslines do %d\n", 0);
			print_sline(map);
			paths = ft_paths_without_common_edges(map->slines, paths, map,num_of_edges);/////
			paths[0]->num_of_steps_in_paths = iter_count(paths, map);
			printf("\npaths %d\n", 0);
			print_paths(best_paths);
		}
		printf("\npaths %d\n", iter_count(paths, map));
		printf("\nbest_paths %d\n", iter_count(best_paths, map));
		if (ft_change_paths_for_the_best(paths, best_paths))
			break;
		i++;

		printf("\nbest paths %d\n", 0);
		print_paths(best_paths);
	}
	if(check < 0 && !*best_paths)
		put_err("ERROR.There is no path between START and END");
	printf("\nbest paths end %d\n", 0);
	print_paths(best_paths);
	return (best_paths);
}

//если есть общие ребра,то удаляем их и заменяем путь снова через БФ
//проверяем ,за сколько шагов пройдет
//находим еще один путь.во второй комплект путей.смотрим,за сколько шагов пройдет
//если с новым путем быстрее,то добавляем путь
// если медленнее ,выходим из цикла