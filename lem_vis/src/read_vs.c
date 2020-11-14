/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_vs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 15:22:30 by dfigg             #+#    #+#             */
/*   Updated: 2020/11/14 15:22:32 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vis.h>

int		add_vstep(char *str, t_vmap *map)
{
	char **arr;

	arr = ft_strsplit(str, ' ');
	if (!map->step)
	{
		map->step = new_step(arr, map);
		map->last_step = map->step;
	}
	else
	{
		map->last_step->next = new_step(arr, map);
		map->last_step = map->last_step->next;
	}
	free_str(arr);
	return (1);
}

t_vline	*new_line(char **str, t_vmap *map)
{
	t_vline	*new;

	if (!(new = (t_vline*)ft_memalloc(sizeof(t_vline))))
		put_err("ERROR");
	new->p1 = get_point_by_name(map, str[0]);
	new->p2 = get_point_by_name(map, str[1]);
	return (new);
}

int		add_line(char **str, t_vmap *map)
{
	if (!map->line)
	{
		map->line = new_line(str, map);
		map->last_line = map->line;
	}
	else
	{
		map->last_line->next = new_line(str, map);
		map->last_line = map->last_line->next;
	}
	return (1);
}

void	pars_line(char *str, t_vmap *map, int mod_command)
{
	char **arr;

	if (ft_find_err(str))
		put_err("ERROR");
	else if (str[0] == 'L')
	{
		add_vstep(str, map);
	}
	else if (ft_find_count(str, ' ') != -1)
	{
		arr = ft_strsplit(str, ' ');
		add_vpoint(arr, map, mod_command);
		free_str(arr);
	}
	else if (ft_find_count(str, '-') != -1)
	{
		arr = ft_strsplit(str, '-');
		add_line(arr, map);
		free_str(arr);
	}
	else if (map->count_ants == -1)
	{
		ft_check_num_ants(str);
		map->count_ants = ft_atoi_check(str);
	}
}

t_vmap	*read_map(void)
{
	int		mod_command;
	char	*line;
	t_vmap	*map;

	mod_command = 0;
	map = init_vmap();
	line = NULL;
	while (get_next_line(0, &line))
	{
		if (mod_command == 1 && (ft_strequ(line, "##start")
								|| ft_strequ(line, "##end")))
			put_err("ERROR.Duplicate line ##start or ##end");
		if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
			mod_command = (ft_strequ(line, "##start")) ? START : END;
		else if (line[0] != '#')
		{
			pars_line(line, map, mod_command);
			mod_command = 0;
		}
		ft_strdel(&line);
	}
	return (map);
}
