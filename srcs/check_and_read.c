#include "lem-in.h"

int		ft_atoi_check(const char *str)
{
	int			i;
	int			sig;
	int long	rez;

	i = 0;
	sig = 1;
	rez = 0;
	if (str[i] == '-')
		sig = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		rez = rez * 10 + (str[i] - '0');
		i++;
	}
	if (i == 0 || rez > INT32_MAX)
		put_err("Not valid int");
	return (sig * (int)rez);
}

void	check_st_end(t_data *map, int mod_command)
{
	if (mod_command == START && map->start)
		put_err("ERROR. 2-nd start");
	else if (mod_command == END && map->end)
		put_err("ERROR. 2-nd end");
}

void	chek_point_in_line(t_data *map)
{
	int		count;
	t_point	*point;

	count = 0;
	point = map->points;
	while (point)
	{
		if (point->p != 2 && ft_strequ(point->name, map->last_lines->p_first))
		{
			map->last_lines->num_first = point->num;
			count++;
		}
		if (point->p != 2 && ft_strequ(point->name, map->last_lines->p_next))
		{
			map->last_lines->num_next = point->num;
			count++;
		}
		point = point->next;
	}
	if (count != 2)
		put_err("invalid line");
}

void	check_line(t_data *map)
{
	t_line	*line;

	chek_point_in_line(map);
	line = map->lines;
	while (line)
	{
		if (line != map->last_lines &&
			line->num_first == map->last_lines->num_first &&
			line->num_next == map->last_lines->num_next)
			put_err("Line. Duplicate error");
		line = line->next;
	}
}
//
//void	check_start_end_connected(t_data *map)
//{
//	t_line	*cline;
//	int		st;
//	int		end;
//
//	st = 0;
//	end = 0;
//	cline = map->lines;
//	while (cline)
//	{
//		if (cline->num_first == map->start->num
//		|| cline->num_next == map->start->num)
//			st++;
//		if (cline->num_first == map->end->num
//		|| cline->num_next == map->end->num)
//			end++;
//		cline = cline->next;
//	}
//	if (st == 0 || end == 0)
//		put_err("ERROR. No valid paths");
//}