/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 15:19:11 by dfigg             #+#    #+#             */
/*   Updated: 2020/11/14 15:19:14 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vis.h>

void	find_max_xy(t_vmap *map, t_visual *v)
{
	t_vpoint	*p;

	v->max_x = 0;
	v->max_y = 0;
	p = map->points;
	while (p)
	{
		if (p->x > v->max_x)
			v->max_x = p->x;
		if (p->y > v->max_y)
			v->max_y = p->y;
		p = p->next;
	}
}

void	set_buf(t_visual *v)
{
	char	*buf;

	if (!(buf = (char*)ft_memalloc(W_HEIGTH * W_WEIDTH * 4)))
		put_err("ERROR");
	ft_memcpy(buf, v->addr, (W_HEIGTH * W_WEIDTH * 4));
	v->buf = buf;
}

void	write_room(t_visual *v, t_vpoint p0, int color, int size)
{
	int	x;
	int	y;

	y = p0.y - size;
	while (y < p0.y + size)
	{
		x = p0.x - size;
		while (x < p0.x + size)
		{
			put_pixel(v, x, y, color);
			x++;
		}
		y++;
	}
}

void	set_vroom(t_visual *v, t_vmap *map)
{
	t_vpoint	*room;
	t_vpoint	p;

	room = map->points;
	while (room)
	{
		p = get_point(room, v);
		if (room == map->start)
			write_room(v, p, YELLOW, 8);
		else if (room == map->end)
			write_room(v, p, GREEN, 8);
		else
			write_room(v, p, WHITE, 8);
		room = room->next;
	}
}

void	ft_drawing(t_vmap *map)
{
	t_visual	*v;
	t_vline		*line;

	v = init_v();
	v->v_map = map;
	clear_image(v);
	find_max_xy(map, v);
	set_vroom(v, map);
	line = map->line;
	while (line)
	{
		set_line(get_point(line->p1, v),
				get_point(line->p2, v), v);
		line = line->next;
	}
	set_buf(v);
	v->ants = init_ants(map, v);
	print_all(v);
	control(v);
	v->v_map->last_step = v->v_map->step;
	mlx_loop_hook(v->mlx, run_ants, v);
	mlx_loop(v->mlx);
}
