/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 15:22:01 by dfigg             #+#    #+#             */
/*   Updated: 2020/11/14 15:22:04 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

t_vmap		*init_vmap(void)
{
	t_vmap	*map;

	if (!(map = (t_vmap*)ft_memalloc(sizeof(t_vmap))))
		put_err("ERROR");
	map->vpath = NULL;
	map->points = NULL;
	map->last_points = NULL;
	map->count_ants = -1;
	return (map);
}

t_visual	*init_v(void)
{
	t_visual *v;

	v = (t_visual*)ft_memalloc(sizeof(t_visual));
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, W_HEIGTH, W_WEIDTH, "LEM_IN");
	v->img = mlx_new_image(v->mlx, W_WEIDTH, W_HEIGTH);
	v->addr = mlx_get_data_addr(v->img, &v->bit_per_pixel, &v->size_line,
							&v->endian);
	v->speed = 1;
	return (v);
}

t_ants		*init_ants(t_vmap *map, t_visual *v)
{
	int		i;
	t_ants	*ant;

	if (!(ant = (t_ants*)ft_memalloc(sizeof(t_ants) *
			(map->count_ants + 1))))
		put_err("ERROR");
	i = 1;
	while (i <= map->count_ants)
	{
		ant[i].prev = get_point(map->start, v);
		ant[i].next = get_point(map->start, v);
		ant[i].cur = get_point(map->start, v);
		ant[i].name = ft_itoa(i);
		ant[i].num = i;
		ant[i].color = ((i * 7 % 200) + 55) << 16;
		ant[i].color |= ((-(int)ant[i].name % 200) + 55) << 8;
		ant[i].color |= ((int)ant[i].name * i) % 200 + 55;
		i++;
	}
	return (ant);
}

void		one_new(t_vstep *new, char *str, t_vmap *map)
{
	char	**tmp;

	tmp = ft_strsplit(str, '-');
	if (!new->last_vpoint)
	{
		new->last_vpoint = copy_vpoint(get_point_by_name(map, tmp[1]));
		new->vpoint = new->last_vpoint;
	}
	else
	{
		new->last_vpoint->next = copy_vpoint(get_point_by_name(map, tmp[1]));
		new->last_vpoint = new->last_vpoint->next;
	}
	new->last_vpoint->ant = ft_strdup(tmp[0] + 1);
	free_str(tmp);
}

t_vstep		*new_step(char **str, t_vmap *map)
{
	int			i;
	t_vstep		*new;

	if (!(new = (t_vstep*)ft_memalloc(sizeof(t_vstep))))
		put_err("ERROR");
	i = 0;
	while (str[i])
	{
		one_new(new, str[i], map);
		i++;
	}
	new->next = NULL;
	return (new);
}
