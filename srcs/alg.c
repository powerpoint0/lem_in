#include "lem-in.h"

void	ft_free_all_in_alg(t_path **paths, t_sline *slines)
{
	t_sline	*prev_slines;

	while (slines)
	{
		prev_slines = slines;
		slines = slines->next;
		free(prev_slines);
	}
	ft_free_all_paths(paths);
	if(paths)
		free(paths);
}

t_path**    ft_paths_without_common_edges(t_sline *slines, t_path **paths, t_data *map)
{
	int        i;
	int        num_paths;

	i = 0;
	num_paths = 0;
	ft_init_slines(slines);

	while(paths[i++])
		num_paths++;
	ft_free_all_paths(paths);
	i = 0;
	while (!ft_bellman_ford(map) && i < num_paths)
	{
		paths[i] = ft_create_path(map);
		if(ft_change_edge(map->slines))
			paths = ft_paths_without_common_edges(map->slines, paths, map);
		i++;
	}
	return (paths);
}

t_path  *ft_copy_in_best_one_path(t_path *path)
{
	t_path  *best_path;
	t_path  *header;
	t_path  *new_point;

	best_path = NULL;
	while(path)
	{
		if(!(new_point = (t_path *) ft_memalloc(sizeof(t_path))))
			put_err("ERROR.No memory for malloc");
		new_point->points = path->points;
		if(best_path)
		{
			new_point->prev = best_path;
			best_path->next = new_point;
		}
		else
			header = new_point;
		best_path = new_point;
		path = path->next;
	}
	best_path = header;
	return(best_path);
}

void		ft_copy_in_best_paths(t_path **paths,t_path **best_paths)
{
	int i;
	i = 0;
	while(paths[i])
	{
		best_paths[i] = ft_copy_in_best_one_path(paths[i]);
		i++;
	}
	best_paths[0]->num_of_steps_in_paths = paths[0]->num_of_steps_in_paths;
}

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
		ft_free_all_paths(best_paths);
		ft_copy_in_best_paths(paths, best_paths);
	}
	else if (paths[0]->num_of_steps_in_paths > best_paths[0]->num_of_steps_in_paths)
		return (-1);
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
	while(!(check = ft_bellman_ford(map)))
	{
		paths[i] = ft_create_path(map);
		if (ft_change_edge(map->slines))
			paths = ft_paths_without_common_edges(map->slines, paths, map);
		if (ft_change_paths_for_the_best(paths, best_paths, map))
			break;
		i++;
	}
	if(check < 0 && !*best_paths)
		put_err("ERROR.There is no path between START and END");
	ft_free_all_in_alg(paths,map->slines);
//	ft_check_repeat_rooms(best_paths);
//
//	printf("\nbest paths end %d\n", 0);
//	print_paths(best_paths);
//	printf("\nbest paths end %d\n", 0);

	 return (best_paths);
}

//ft_check_repeat_rooms(best_paths);
//	printf("\nbest paths end %d\n", 0);
//	print_paths(best_paths);
//	printf("\nbest paths end %d\n", 0);
