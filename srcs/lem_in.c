/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:27:58 by cjoaquin          #+#    #+#             */
/*   Updated: 2020/11/13 20:28:02 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_all(t_data *map, t_path **best_paths)
{
	t_point	*prev_points;
	t_line	*prev_lines;

	ft_free_all_paths(best_paths);
	while (map && map->points)
	{
		prev_points = map->points;
		map->points = map->points->next;
		free_point(prev_points);
	}
	while (map && map->lines)
	{
		prev_lines = map->lines;
		map->lines = map->lines->next;
		free_line(prev_lines);
	}
	free(map);
	free(best_paths);
}

int			put_err(char *str)
{
	ft_putendl_fd(str, 1);
	exit(1);
}

/*
** reading with files
**int 	main(int argc, char **argv)
**if (argc < 2)
**put_err("ERROR.No file for reading");
**fd = (ft_strequ(argv[1], "<")) ? open(argv[2], O_RDONLY)
** : open(argv[1], O_RDONLY);
**if (fd < 0)
**put_err("ERROR.File did not open");
*/

/*
** time in program
** #include <time.h>
** clock_t go_1 = clock();
** ft_let_go_ants(best_paths, map);
** clock_t go_2 = clock();
** double go_diff = (double) (go_2 - go_1)/CLOCKS_PER_SEC;
** ft_printf("Go time = %f\n", go_diff);
*/

int			main(void)
{
	int		fd;
	t_data	*map;
	t_path	**best_paths;

	map = NULL;
	best_paths = NULL;
	fd = 0;
	map = read_map(fd);
	best_paths = ft_alg(map);
	ft_let_go_ants(best_paths, map);
	free_all(map, best_paths);
	return (0);
}
