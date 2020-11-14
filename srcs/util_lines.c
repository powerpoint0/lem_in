/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:29:39 by cjoaquin          #+#    #+#             */
/*   Updated: 2020/11/13 20:29:41 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				ft_find_counts(const char *s, int c)
{
	int			i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if ((char)c == '\0')
		return (i);
	return (-1);
}

void			copy_one_point2(t_point *point)
{
	t_point		*new;

	if (!(new = (t_point*)ft_memalloc(sizeof(t_point))))
		put_err("ERROR.No memory for malloc");
	ft_memcpy(new, point, sizeof(t_point));
	new->snum = point->snum + 1;
	new->p = 2;
	new->next = point->next;
	point->next = new;
}

void			copy_points2(t_data *map)
{
	t_point		*point;

	point = map->last_points;
	if (point != map->start &&
		point != map->end)
	{
		copy_one_point2(point);
		map->last_points = point->next;
	}
}

void			free_line(t_line *line)
{
	if (line)
	{
		free(line->p_first);
		free(line->p_next);
	}
	free(line);
}
