#include "lem-in.h"

void	free_str(char **str)
{
	int	i;

	i = 0;
	if(str)
	{
		while(str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

void	delete_point(t_data *map, int num_point)
{
	t_point	*delete;
	t_point	*prev;

	prev = map->points;
	while (prev->next->num != num_point)
	{
		prev = prev->next;
	}
	delete = prev->next;
	if (delete->next)
		prev->next = delete->next;
	else
		prev->next = NULL;
	free(delete);
	delete = NULL;
}

void	del_free_point(t_data *map)
{
	t_point	*cpoint;
	t_line	*cline;
	int		num;
	int		ok;

	cpoint = map->points;
	while (cpoint)
	{
		ok = 0;
		cline = map->lines;
		while (cline)
		{
			if (cline->num_first == cpoint->num ||
					cline->num_next == cpoint->num)
				ok++;
			cline = cline->next;
		}
		num = cpoint->num;
		cpoint = cpoint->next;
		if (!ok)
			delete_point(map, num);
	}
}

t_data	*read_map(int fd)
{
	int		rd;
	int		mod_command;
	char	*line;
	t_data	*map;

	mod_command = 0;
	map = int_map();
	double sum = 0;
	while ((rd = get_next_line(fd, &line)))
	{
		if (rd == -1)
			put_err("Not read file");
		ft_putendl(line);
		if (mod_command == 1 && (ft_strequ(line, "##start")
			|| ft_strequ(line, "##end")))
			put_err("ERROR. more line ##start or ##end");
		if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
			mod_command = (ft_strequ(line, "##start")) ? START : END;
		else if (line[0] != '#')
		{
			clock_t parsing_1 = clock();
			parsing_line(line, map, mod_command);
			clock_t parsing_2 = clock();
			double parsing_diff = (double) (parsing_2 - parsing_1)/CLOCKS_PER_SEC;
			sum += parsing_diff;
			mod_command = 0;
		}
	}
	printf("Parsing time = %f\n", sum);
	if (!map->start || !map->end)
		put_err("ERROR.Not start or end");

	//check_start_end_connected(map);
	//del_free_point(map);
		clock_t copy_points_1 = clock();
	copy_points(map);
		clock_t copy_points_2 = clock();
	double copy_points_diff = (double) (copy_points_2 - copy_points_1)/CLOCKS_PER_SEC;
	printf("Copy_points time = %f\n", copy_points_diff);
	clock_t slines_1 = clock();
		map->slines = set_sline(map);
	clock_t slines_2 = clock();
	double slines_diff = (double) (slines_2 - slines_1)/CLOCKS_PER_SEC;
	printf("Set_sline time = %f\n", slines_diff);
	if (line)
		free(line);
	return (map);
}
