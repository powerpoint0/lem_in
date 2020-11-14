/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 15:19:00 by dfigg             #+#    #+#             */
/*   Updated: 2020/11/14 15:19:02 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vis.h>

int		ft_close(t_visual *v)
{
	mlx_destroy_window(v->mlx, v->win);
	exit(0);
}

int		key_press(int key, t_visual *v)
{
	if (key == KEY_ESC)
		ft_close(v);
	if (key == KEY_SPACE)
	{
		v->pause = !v->pause;
	}
	if (key == KEY_UP && v->speed < 10)
		v->speed++;
	if (key == KEY_DOWN && v->speed > 1)
		v->speed--;
	return (0);
}

void	control(t_visual *v)
{
	mlx_hook(v->win, 17, 0, ft_close, v);
	mlx_key_hook(v->win, key_press, v);
}
