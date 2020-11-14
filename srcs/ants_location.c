/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_location.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:29:27 by cjoaquin          #+#    #+#             */
/*   Updated: 2020/11/13 20:29:30 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			add_ant(t_path *path, t_data *map, int ants)
{
	if (ants == 0)
		path->points->ant_num = -1;
	else
	{
		map->ants_count++;
		path->points->ant_num = map->ants_count;
		add_loc(map, path->points->name, path->points->ant_num);
		ants--;
	}
	return (ants);
}

t_loc		*set_new_loc(char *name, int num_ant)
{
	t_loc	*new;

	if (!(new = (t_loc*)ft_memalloc(sizeof(t_loc))))
		put_err("ERROR.No memory for malloc");
	new->name = name;
	new->i = num_ant;
	new->next = NULL;
	return (new);
}

void		del_location(t_data *map)
{
	t_loc	*del;

	while (map->location)
	{
		del = map->location;
		map->location = map->location->next;
		free(del);
		del = NULL;
	}
}

void		ins_loc(t_data *map, char *name, int num_ant)
{
	t_loc	*new;
	t_loc	*next;
	t_loc	*loc;

	loc = map->location;
	new = set_new_loc(name, num_ant);
	if (loc->i > num_ant)
	{
		next = loc;
		new->next = next;
		map->location = new;
	}
	else
	{
		while (loc->next && loc->next->i <= num_ant)
			loc = loc->next;
		if (!loc->next)
			loc->next = new;
		else if (loc->i < num_ant)
		{
			next = loc->next;
			loc->next = new;
			new->next = next;
		}
	}
}

void		add_loc(t_data *map, char *name, int num_ant)
{
	if (!map->location)
		map->location = set_new_loc(name, num_ant);
	else
		ins_loc(map, name, num_ant);
}
