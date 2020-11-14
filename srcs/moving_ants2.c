/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_ants2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:28:13 by cjoaquin          #+#    #+#             */
/*   Updated: 2020/11/13 20:28:16 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			ft_set_count_n_ants(t_path **paths, int *ant_in_path,
								int count, int *i)
{
	if (count == 0)
	{
		ant_in_path[count]++;
		count++;
	}
	else if (paths[count]->len < (ant_in_path[count - 1] +
								paths[count - 1]->len))
	{
		ant_in_path[count]++;
		count++;
	}
	else
	{
		count = 0;
		(*i)--;
	}
	return (count);
}

int			*set_ant_in_path(t_path **paths, t_data *map)
{
	int		*ant_in_path;
	int		size;
	int		i;
	int		count;

	size = get_num_path(paths);
	if (!(ant_in_path = (int*)ft_memalloc(sizeof(int) * size)))
		put_err("ERROR.No memory for malloc.Ants");
	set_len_paths(paths, map);
	i = 0;
	count = 0;
	while (i < map->num_ants)
	{
		count = ft_set_count_n_ants(paths, ant_in_path, count, &i);
		if (count == size)
			count = 0;
		i++;
	}
	return (ant_in_path);
}
