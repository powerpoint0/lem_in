/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 15:18:48 by dfigg             #+#    #+#             */
/*   Updated: 2020/11/14 15:18:50 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

int			cur_point(int p1, int p2, int d)
{
	int p;

	p = p1 + d * (p2 - p1) / RANGE;
	return (p);
}

t_vpoint	calc_point(t_vpoint *p1, t_vpoint *p2, int d)
{
	t_vpoint	cur;

	cur.x = cur_point(p1->x, p2->x, d);
	cur.y = cur_point(p1->y, p2->y, d);
	return (cur);
}

void		ant_step(t_visual *v)
{
	int		count;
	int		i;
	t_ants	*ant;

	if (v->way > RANGE)
		return ;
	ant = v->ants;
	count = v->v_map->count_ants;
	i = 1;
	while (i <= count)
	{
		ant[i].cur = calc_point(&ant[i].prev, &ant[i].next, v->way);
		i++;
	}
	v->way += v->speed;
}

int			ant_new_step(t_visual *v)
{
	t_vpoint	*p;
	t_ants		*ant;
	int			i;

	if (v->way <= RANGE)
		return (0);
	if (!v->v_map->last_step)
	{
		v->finish = 1;
		return (0);
	}
	p = v->v_map->last_step->vpoint;
	ant = v->ants;
	v->way = 0;
	while (p)
	{
		i = ft_atoi(p->ant);
		ant[i].prev = ant[i].next;
		ant[i].next = get_point(p, v);
		p = p->next;
	}
	return (1);
}

int			run_ants(t_visual *v)
{
	if (!v->pause)
	{
		ant_step(v);
		if (ant_new_step(v))
			v->v_map->last_step = v->v_map->last_step->next;
	}
	print_all(v);
	return (0);
}
