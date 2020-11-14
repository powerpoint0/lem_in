/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:26:25 by cjoaquin          #+#    #+#             */
/*   Updated: 2020/11/13 20:26:32 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			ft_change_edge(t_sline *slines)
{
	t_point	*tmp;
	int		common_edges;

	common_edges = 0;
	while (slines)
	{
		if (slines->out->in_path && slines->in->in_path &&
		slines->out->prev_room_path == slines->in && slines->close != CLOSE)
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
	return (common_edges);
}

t_path		*ft_create_path(t_data *map)
{
	t_path	*path;
	t_path	*new_point;
	t_point	*point;

	path = NULL;
	point = map->end;
	while (point)
	{
		if (!(new_point = (t_path*)ft_memalloc(sizeof(t_path))))
			put_err("ERROR.No memory for malloc");
		if (path)
			path->prev = new_point;
		new_point->next = path;
		new_point->points = point;
		new_point->points->in_path = 2;
		path = new_point;
		if (path->points == map->start)
			break ;
		point = point->prev_room_path;
	}
	return (path);
}

t_path		**ft_paths_without_common_edges(t_sline *slines,
										t_path **paths, t_data *map)
{
	int		i;
	int		num_paths;

	i = 0;
	num_paths = 0;
	ft_init_slines(slines);
	while (paths[i++])
		num_paths++;
	ft_free_all_paths(paths);
	i = 0;
	while (!ft_bellman_ford(map) && i < num_paths)
	{
		paths[i] = ft_create_path(map);
		if (ft_change_edge(map->slines))
			paths = ft_paths_without_common_edges(map->slines, paths, map);
		i++;
	}
	return (paths);
}

int			ft_change_paths_for_the_best(t_path **paths,
									t_path **best_paths, t_data *map)
{
	if (!*best_paths)
	{
		ft_copy_in_best_paths(paths, best_paths);
		return (0);
	}
	paths[0]->num_steps_in_paths = iter_count(paths, map);
	best_paths[0]->num_steps_in_paths = iter_count(best_paths, map);
	if (paths[0]->num_steps_in_paths <= best_paths[0]->num_steps_in_paths)
	{
		ft_free_all_paths(best_paths);
		ft_copy_in_best_paths(paths, best_paths);
	}
	else if (paths[0]->num_steps_in_paths > best_paths[0]->num_steps_in_paths)
		return (-1);
	return (0);
}

t_path		**ft_alg(t_data *map)
{
	t_path	**paths;
	t_path	**best_paths;
	int		check;
	int		i;

	i = 0;
	ft_num_of_max_paths(map);
	paths = ft_init_paths(map);
	best_paths = ft_init_paths(map);
	while (!(check = ft_bellman_ford(map)))
	{
		paths[i] = ft_create_path(map);
		if (ft_change_edge(map->slines))
			paths = ft_paths_without_common_edges(map->slines, paths, map);
		if (ft_change_paths_for_the_best(paths, best_paths, map))
			break ;
		i++;
	}
	if (check < 0 && !*best_paths)
		put_err("ERROR.There is no path between START_POINT and END_POINT");
	ft_free_all_in_alg(paths, map->slines);
	return (best_paths);
}

/*
**ft_check_repeat_rooms(best_paths);
**	ft_printf("\nbest paths end %d\n", 0);
**	print_paths(best_paths);
**	ft_printf("\nbest paths end %d\n", 0);
*/
