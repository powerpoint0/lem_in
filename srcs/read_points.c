/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:28:56 by cjoaquin          #+#    #+#             */
/*   Updated: 2020/11/13 20:28:58 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_point	*get_point(t_data *map, int num, int p)
{
	t_point	*cpoint;

	cpoint = map->points;
	while (cpoint->num != num || cpoint->p != p)
		cpoint = cpoint->next;
	return (cpoint);
}

t_point	*new_point(char **str, int num)
{
	t_point	*new;

	if (!(new = (t_point*)ft_memalloc(sizeof(t_point))))
		put_err("Init.Not create point");
	new->num = num;
	new->snum = -1;
	new->ant_num = -1;
	new->p = 1;
	new->name = str[0];
	new->x = ft_atoi_check(str[1]);
	new->y = ft_atoi_check(str[2]);
	new->in_path = 0;
	new->next = NULL;
	return (new);
}

void	free_point(t_point *point)
{
	if (point && point->p != 2)
		free(point->name);
	free(point);
}

int		add_point(char **str, t_data *map, int mod_command)
{
	check_st_end(map, mod_command);
	if (!map->points)
	{
		map->points = new_point(str, 0);
		map->last_points = map->points;
	}
	else
	{
		check_duplicate(map, str[0]);
		map->last_points->next = new_point(str, (map->last_points->num + 1));
		map->last_points = map->last_points->next;
	}
	if (mod_command == START)
		map->start = map->last_points;
	if (mod_command == END)
		map->end = map->last_points;
	str[0] = NULL;
	free_str(str, 3);
	return (1);
}
