/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:29:27 by cjoaquin          #+#    #+#             */
/*   Updated: 2020/11/13 20:29:30 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			get_num_path(t_path **paths)
{
	int		num;

	num = 0;
	while (paths[num])
		num++;
	return (num);
}

void		set_len_paths(t_path **paths, t_data *map)
{
	int		len;
	t_path	*path;
	int		i;

	i = 0;
	while (paths[i])
	{
		len = 0;
		path = paths[i];
		while (path->points->num != map->end->num)
		{
			if (path->points->num != path->next->points->num)
				len++;
			path = path->next;
		}
		paths[i]->len = len;
		i++;
	}
}

void		cut_path(t_path **paths, t_data *map)
{
	t_path	*path;
	t_path	*next;
	int		i;

	i = 0;
	while (paths[i])
	{
		path = paths[i];
		while (path->points->num != map->end->num)
		{
			if (path->points->num == path->next->points->num)
			{
				next = path->next;
				path->next = path->next->next;
				path->next->prev = path;
				free(next);
			}
			else
				path = path->next;
		}
		i++;
	}
}

int			iter_count(t_path **paths, t_data *map)
{
	int		i;
	int		pcount;
	int		count;
	int		*ants;

	i = 0;
	count = 0;
	pcount = 0;
	if (!*paths)
		return (INF);
	ants = set_ant_in_path(paths, map);
	while (paths[i] && ants[i] > 0)
	{
		count = paths[i]->len + (ants[i] - 1);
		if (pcount != 0 && count < pcount)
			count = pcount;
		pcount = count;
		i++;
	}
	if (ants)
		free(ants);
	return (count);
}

void		prt_path(t_path **paths)
{
	int		i;
	t_path	*path;

	i = 0;
	while (paths[i])
	{
		path = paths[i];
		while (path)
		{
			ft_printf("%s(%d)\t", path->points->name, path->points->ant_num);
			path = path->next;
		}
		ft_printf("\n");
		i++;
	}
}
