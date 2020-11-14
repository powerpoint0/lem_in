/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 15:21:41 by dfigg             #+#    #+#             */
/*   Updated: 2020/11/14 15:21:44 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

void		put_pixel(t_visual *v, int x, int y, int color)
{
	int	i;

	if (x < W_WEIDTH && y >= 0 && y < W_HEIGTH)
	{
		i = (x * v->bit_per_pixel / 8) + (y * v->size_line);
		v->addr[i] = (char)color;
		v->addr[++i] = (char)(color >> 8);
		v->addr[++i] = (char)(color >> 16);
	}
}

void		clear_image(t_visual *v)
{
	int	x;
	int	y;

	y = 0;
	while (y < W_HEIGTH)
	{
		x = 0;
		while (x < W_WEIDTH)
		{
			put_pixel(v, x, y, BLACK);
			x++;
		}
		y++;
	}
}

void		print_all(t_visual *v)
{
	t_vpoint	*p;
	t_vpoint	tmp;

	ft_memcpy(v->addr, v->buf, (W_WEIDTH * W_HEIGTH * 4));
	if (!v->finish)
		print_ants(v);
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
	p = v->v_map->points;
	while (p)
	{
		tmp = get_point(p, v);
		mlx_string_put(v->mlx, v->win, tmp.x, (tmp.y - 32), SILVER, p->name);
		p = p->next;
	}
	if (!v->finish)
		print_ants_names(v);
	if (!v->v_map->last_step)
		return ;
}

void		on_off_ant(t_visual *v, t_vpoint p, int color, int size)
{
	int	x;
	int	y;

	y = p.y - size;
	while (y < p.y + size)
	{
		x = p.x - size;
		while (x < p.x + size)
		{
			put_pixel(v, x, y, color);
			x++;
		}
		y++;
	}
}

t_vpoint	get_point(t_vpoint *p, t_visual *v)
{
	t_vpoint	point;
	int			x;
	int			y;

	x = p->x;
	y = p->y;
	ft_bzero(&point, sizeof(t_vpoint));
	point.x = x * W_WEIDTH / v->max_x * 3 / 4 + 50;
	point.y = y * W_HEIGTH / v->max_y * 3 / 4 + 50;
	point.ant = p->ant;
	return (point);
}
