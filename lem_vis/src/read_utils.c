/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 15:22:16 by dfigg             #+#    #+#             */
/*   Updated: 2020/11/14 15:22:22 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

int			ft_check_num_ants(char *str)
{
	if (*str == '0')
		put_err("ERROR.Invalid num of ants");
	while (*str)
		if (!ft_isdigit(*str++))
			put_err("ERROR.Invalid num of ants");
	return (0);
}

t_vpoint	*get_point_by_name(t_vmap *map, char *name)
{
	t_vpoint	*cpoint;

	cpoint = map->points;
	while (ft_strcmp(cpoint->name, name))
		cpoint = cpoint->next;
	return (cpoint);
}

t_vpoint	*new_point(char **str)
{
	t_vpoint	*new;

	if (!(new = (t_vpoint*)ft_memalloc(sizeof(t_vpoint))))
		put_err("Init.Not create point");
	new->name = ft_strdup(str[0]);
	new->x = ft_atoi_check(str[1]);
	new->y = ft_atoi_check(str[2]);
	new->z = 0;
	new->color = WHITE;
	return (new);
}

int			add_vpoint(char **str, t_vmap *map, int mod_command)
{
	if (!map->points)
	{
		map->points = new_point(str);
		map->last_points = map->points;
	}
	else
	{
		map->last_points->next = new_point(str);
		map->last_points = map->last_points->next;
	}
	if (mod_command == START)
		map->start = map->last_points;
	if (mod_command == END)
		map->end = map->last_points;
	return (1);
}

t_vpoint	*copy_vpoint(t_vpoint *point)
{
	t_vpoint	*new;

	if (!(new = (t_vpoint*)ft_memalloc(sizeof(t_vpoint))))
		put_err("ERROR.No memory for malloc");
	ft_memcpy(new, point, sizeof(t_vpoint));
	new->next = NULL;
	return (new);
}
