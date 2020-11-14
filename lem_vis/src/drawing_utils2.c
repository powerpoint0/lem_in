/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 15:21:50 by dfigg             #+#    #+#             */
/*   Updated: 2020/11/14 15:21:52 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

void	print_ants_names(t_visual *v)
{
	int			count;
	int			i;
	t_ants		*ant;
	t_vpoint	start;

	start = get_point(v->v_map->start, v);
	ant = v->ants;
	count = v->v_map->count_ants;
	i = 1;
	while (i <= count)
	{
		if (!(start.x == ant[i].next.x && start.y == ant[i].next.y))
			mlx_string_put(v->mlx, v->win, ant[i].cur.x, (ant[i].cur.y + 6),
				SILVER, ant[i].name);
		i++;
	}
}

void	print_ants(t_visual *v)
{
	int		count;
	int		i;
	t_ants	*ant;

	ant = v->ants;
	count = v->v_map->count_ants;
	i = 1;
	while (i <= count)
	{
		on_off_ant(v, ant[i].cur, ant[i].color, 6);
		i++;
	}
}

int		ft_abs(int a, int b)
{
	return (a < b ? b - a : a - b);
}

void	set_first_point(t_vpoint *p0, int *p)
{
	p[0] = p0->x;
	p[1] = p0->y;
	p[2] = p0->color;
}

void	set_line(t_vpoint p0, t_vpoint p1, t_visual *v)
{
	int		dserr[6];
	int		p[3];

	dserr[0] = ft_abs(p0.x, p1.x);
	dserr[2] = (p0.x < p1.x) ? 1 : -1;
	dserr[1] = -ft_abs(p0.y, p1.y);
	dserr[3] = (p0.y < p1.y) ? 1 : -1;
	dserr[4] = dserr[0] + dserr[1];
	set_first_point(&p0, p);
	while (p[0] != p1.x || p[1] != p1.y)
	{
		put_pixel(v, p[0], p[1], WHITE);
		if ((dserr[5] = dserr[4] * 2) >= dserr[1])
		{
			dserr[4] += dserr[1];
			p[0] += dserr[2];
		}
		if (dserr[5] <= dserr[0])
		{
			dserr[4] += dserr[0];
			p[1] += dserr[3];
		}
	}
}
