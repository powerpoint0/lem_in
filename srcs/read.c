/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:28:29 by cjoaquin          #+#    #+#             */
/*   Updated: 2020/11/13 20:28:32 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_str(char **str, int num)
{
	int	i;

	i = 0;
	if (str)
	{
		while (i < num)
		{
			ft_strdel(&str[i]);
			i++;
		}
		free(str);
	}
}

int		ft_check_n_parsing(int mod_command, char *line, t_data *map)
{
	if (mod_command == 1 && (ft_strequ(line, "##start")
							|| ft_strequ(line, "##end")))
		put_err("ERROR.Duplicate line ##start or ##end");
	if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
		mod_command = (ft_strequ(line, "##start")) ? START_POINT : END_POINT;
	else if (line[0] != '#')
	{
		parsing_line(line, map, mod_command);
		mod_command = 0;
	}
	return (mod_command);
}

t_data	*read_map(int fd)
{
	int		rd;
	int		mod_command;
	char	*line;
	t_data	*map;

	mod_command = 0;
	map = int_map();
	while ((rd = get_next_line(fd, &line)))
	{
		if (rd == -1)
			put_err("ERROR.Empty file");
		ft_putendl(line);
		mod_command = ft_check_n_parsing(mod_command, line, map);
		if (line)
			ft_strdel(&line);
	}
	write(1, "\n", 1);
	if (!map->start || !map->end)
		put_err("ERROR.There is no start or end");
	map->slines = set_slines(map);
	return (map);
}
