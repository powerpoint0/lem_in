/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:28:13 by cjoaquin          #+#    #+#             */
/*   Updated: 2020/11/13 20:28:16 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_move_by_path2(t_path *path, t_data *map, int *ants, int i)
{
	while (path->points->num != map->end->num)
		path = path->next;
	while (path->prev)
	{
		if (path->prev->points->num != map->start->num)
		{
			path->points->ant_num = path->prev->points->ant_num;
			if (path->points->ant_num != -1)
				add_loc(map, path->points->name, path->points->ant_num);
		}
		else
			ants[i] = add_ant(path, map, ants[i]);
		if (path->points->num == map->end->num && path->points->ant_num != -1)
		{
			path->points->ant_num = -1;
			map->ants_end++;
		}
		path = path->prev;
	}
}

void		ft_move_by_path(t_path **paths, t_data *map, int *ants)
{
	int		i;
	t_path	*path;

	i = 0;
	while (paths[i])
	{
		path = paths[i];
		ft_move_by_path2(path, map, ants, i);
		i++;
	}
}

void		print_position(t_loc *location)
{
	t_loc	*ploc;

	ploc = location;
	while (ploc)
	{
		write(1, "L", 1);
		ft_putnbr(ploc->i);
		write(1, "-", 1);
		ft_putstr(ploc->name);
		if (ploc->next)
			write(1, " ", 1);
		ploc = ploc->next;
	}
	write(1, "\n", 1);
}

int			ft_let_go_ants(t_path **paths, t_data *map)
{
	int		*ants;

	map->ants_end = 0;
	map->ants_count = 0;
	cut_path(paths, map);
	ants = set_ant_in_path(paths, map);
	while (map->ants_end != map->num_ants)
	{
		ft_move_by_path(paths, map, ants);
		print_position(map->location);
		del_location(map);
	}
	if (ants)
		free(ants);
	return (0);
}
