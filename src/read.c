#include "lem_in.h"

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
	if (i == 0 || rez > INT_MAX)
		put_err("Not valid int");
	return (sig * (int)rez);
}

int		ft_find_count(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if ((char)c == '\0')
		return (i);
	return (-1);
}

t_point	*new_point(char **str, int num)
{
	t_point	*new;

	if (!(new = (t_point*)ft_memalloc(sizeof(t_point))))
		put_err("Init.Not create point");
	new->num = num;
	new->snum = -1;
	new->p = 1;
	new->name = str[0];
	new->x = ft_atoi_check(str[1]);
	new->y = ft_atoi_check(str[2]);
	new->in_path = 0;
	new->next = NULL;
	new->check = NULL;
	return (new);
}

void	check_st_end(t_data *map, int mod_command)
{
	if (mod_command == START && map->start)
		put_err("ERROR. 2-nd start");
	else if (mod_command == END && map->end)
		put_err("ERROR. 2-nd end");
}

int		add_point(char **str, t_data *map, int mod_command)
{
	int	i;

	i = 0;
	check_st_end(map, mod_command);
	while (str[i] != NULL)
		i++;
	if (i != 3)
		return (0);
	if (!map->points)
	{
		map->points = new_point(str, 0);
		map->last_points = map->points;
	}
	else
	{
		map->last_points->next = new_point(str, (map->last_points->num + 1));
		map->last_points =  map->last_points->next;
	}
	if (mod_command == START)
		map->start = map->last_points;
	if (mod_command == END)
		map->end = map->last_points;
	return (1);
}

t_line	*new_line(char **str)
{
	t_line	*new;

	if (!(new = (t_line*)ft_memalloc(sizeof(t_line))))
		put_err("Init.Not creat line");
	new->p_first = str[0];
	new->p_next = str[1];
	new->next = NULL;
	return (new);
}

void	chek_point_in_line(t_data *map)
{
	int		count;
	t_point	*header;

	count = 0;
	header = map->points;
	while(map->points)
	{
		if (ft_strequ(map->points->name, map->last_lines->p_first))
		{
			map->last_lines->num_first = map->points->num;
			count++;
		}
		if (ft_strequ(map->points->name, map->last_lines->p_next))
		{
			map->last_lines->num_next = map->points->num;
			count++;
		}
		map->points = map->points->next;
	}
	map->points = header;
	if (count != 2)
		put_err("invalid line");
}

void	check_line(t_data *map)
{
	t_line	*header;

	chek_point_in_line(map);
	header = map->lines;
	while (map->lines)
	{
		if(map->lines != map->last_lines &&
		map->lines->num_first == map->last_lines->num_first &&
		map->lines->num_next == map->last_lines->num_next)
			put_err("Line. Duplicate error");
		map->lines = map->lines->next;
	}
	map->lines = header;
}

int		add_line(char **str, t_data *map)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	if (i != 2)
		return (0);
	if (!map->lines)
	{
		map->lines = new_line(str);
		map->last_lines = map->lines;
		check_line(map);
	}
	else
	{
		map->last_lines->next = new_line(str);
		map->last_lines = map->last_lines->next;
		check_line(map);
	}
	return (1);
}

int		parsing_line(char *str, t_data *map, int mod_command)
{
	if (map->num_ants == -1)
		map->num_ants = ft_atoi_check(str);
	else
	{
		if (ft_find_count(str, ' ') != -1)
			add_point(ft_strsplit(str, ' '), map, mod_command);
		else if (ft_find_count(str, '-') != -1)
			add_line(ft_strsplit(str, '-'), map);
	}
	return (1);
}

int	get_arr_size(t_line *line, int	num_point)
{
	t_line	*cline;
	int		size;

	size = 0;
	cline = line;
	while(cline)
	{
		if (cline->num_first == num_point || cline->num_next == num_point)
			size++;
		cline = cline->next;
	}
	return (size);
}

t_point	*get_point(t_data *map, int num)
{
	t_point	*cpoint;

	cpoint = map->points;
	while (cpoint->num != num)
		cpoint = cpoint->next;
	return (cpoint);
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

t_point	**set_arr_lines(t_data *map, t_point *point, int size)
{
	t_point	**arr_lines;
	t_line	*cline;
	int		i;

	cline = map->lines;
	i = 0;
	if (!(arr_lines = (t_point **)ft_memalloc(sizeof(t_point) * size)
			))
		put_err("Something went wrong");
	while (cline)
	{
		if (cline->num_next == point->num)
			arr_lines[i++] = get_point(map, cline->num_first);
		if (cline->num_first == point->num)
			arr_lines[i++] = get_point(map, cline->num_next);
		cline = cline->next;
	}
	point->check = set_check(i);
	return (arr_lines);
}

int		connected_points(t_data *map)
{
	t_point	*cpoint;
	int 	arr_size;

	cpoint = map->points;
	while (cpoint)
	{
		arr_size = get_arr_size(map->lines, cpoint->num);
		if (!arr_size)
			delete_point(map, cpoint->num);
		else
			cpoint->arr_lines = set_arr_lines(map, cpoint, arr_size);
		cpoint = cpoint->next;
	}
	return (1);
}

void	check_start_end_connected(t_data *map)
{
	t_line	*cline;
	int		st;
	int		end;

	st = 0;
	end = 0;
	cline = map->lines;
	while (cline)
	{
		if (cline->num_first == map->start->num || cline->num_next == map->start->num)
			st++;
		if (cline->num_first == map->end->num || cline->num_next == map->end->num)
			end++;
		cline = cline->next;
	}
	if (st == 0 || end == 0)
		put_err("ERROR. No valid paths");
}
/*
void	copy_one_point(t_point *point, int snum)
{
	t_point	*new;
	if (!(new = (t_point*) ft_memalloc(sizeof(t_point))))
		put_err("ERROR. Copy point");

	ft_memcpy(new, point, sizeof(t_point));
	new->snum = snum;
	new->p = 2;
	new->next = point->next;
	point->next = new;
}

void	copy_points(t_data *map)
{
	t_point	*point;
	int		snum;

	snum = 0;
	point = map->points;
	while (point)
	{
		if (point->num != map->start->num &&
			point->num != map->end->num)
		{
			point->snum = snum++;
			copy_one_point(point, snum);
			point = point->next;
		}
		snum++;
		point = point->next;
	}
}
*/
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
/*
int	size_in(t_data *map, int num)
{
	t_line	*cline;
	int		size;

	size = 0;
	cline = map->lines;
	while(cline)
	{
		if (cline->num_next == num)
			size++;
		if (cline->num_first == num)
			size++;
		cline = cline->next;
	}
	return (size);
}

t_point	*get_point2(t_data *map, int num, int	p)
{
	t_point	*cpoint;

	cpoint = map->points;
	if (num == map->start->num)
		return (map->start);
	if (num == map->end->num)
		return (map->end);
	while (cpoint->num != num || cpoint->p != p)
		cpoint = cpoint->next;
	return (cpoint);
}
 */
/*
int		add_to_arrline(t_point **arr_lines, t_point *point, int count)
{
	int	i;
	int	in;
	i = 0;

	in = 0;
	while (i < count)
	{
		if (arr_lines[i]->num == point->num && arr_lines[i]->p == point->p)
			in++;
		i++;
	}
	if (in > 0)
		return (count);
	arr_lines[count] = point;
	return (count + 1);
}
*/
int		*set_check(int size)
{
	int	*check;

	if (size == 0)
		put_err("Something went wrong");
	if (!(check = (int*)ft_memalloc(sizeof(int) * (size + 1))))
		put_err("Something went wrong");
	check[0] = size;
	while (size > 0)
	{
		check[size] = 1;
		size--;
	}
	return (check);
}
/*
t_point	**set_arr_lines_in(t_data *map, t_point *point, int size, int p)
{
	t_point **arr_lines;
	t_line *cline;
	int i;

	cline = map->lines;
	i = 0;
	if (!(arr_lines = (t_point **) ft_memalloc(sizeof(t_point) * size)
	))
		put_err("Something went wrong");
	while (cline)
	{
		if (cline->num_first == point->num && (point->p == 2 || point->p == 0))
			arr_lines[i++] = get_point2(map, cline->num_next, p);
		if (cline->num_next == point->num && point->p == 2)
			arr_lines[i++] = get_point2(map, cline->num_next, p);
		if (cline->num_next == point->num && (point->p == 1 || point->p == 0))
			arr_lines[i++] = get_point2(map, cline->num_first, p);
		if (cline->num_first == point->num && point->p == 1)
			arr_lines[i++] = get_point2(map, cline->num_first, p);

//		if (cline->num_first == point->num && (point->p == 2 || point->p == 0))
//			i = add_to_arrline (arr_lines, get_point2(map, cline->num_next, p), i);
//		if (cline->num_next == point->num && point->p == 2)
//			i = add_to_arrline (arr_lines, get_point2(map, cline->num_next, p), i);
//		if (cline->num_next == point->num && (point->p == 1 || point->p == 0))
//			i = add_to_arrline (arr_lines, get_point2(map, cline->num_first, p), i);
//		if (cline->num_first == point->num && point->p == 1)
//			i = add_to_arrline (arr_lines, get_point2(map, cline->num_first, p), i);
		cline = cline->next;
	}
	point->check = set_check(i);
	return (arr_lines);
}

void	connected_points2(t_data *map)
{
	t_line	*cline;
	t_point	*tpoint;
	int		size;

	cline = map->lines;
	map->start->p = 0;
	map->end->p = 0;
		while (cline)
		{
			size = size_in(map, cline->num_first);
			tpoint = get_point2(map, cline->num_first, 2);
			tpoint->arr_lines = set_arr_lines_in(map, tpoint, size, 1); // добавляем превые точки (из next)
			size = size_in(map, cline->num_next);
			tpoint = get_point2(map, cline->num_next, 1);
			tpoint->arr_lines = set_arr_lines_in(map, tpoint, size, 2); // добавляем вторые точки из first
			cline = cline->next;
		}
}
*/
void	print_arr(t_data *map)
{
	t_point	*point;
	int		i;

	point = map->points;
	while (point)
	{
		if (point->num == map->start->num)
			printf("%s\n", "START POINT");
		if (point->num == map->end->num)
			printf("%s\n", "END POINT");
		printf("%s [%d]:\t", point->name, point->p);
		i = 0;
		while (point->arr_lines[i])
		{
			printf("%s [%d]:\t", point->arr_lines[i]->name, point->arr_lines[i]->p);
			i++;
		}
		printf("\n");
		point = point->next;
	}
}

t_data	*read_map(int fd)
{
	int 	rd;
	int		mod_command;
	char 	*line;
	t_data	*map;

	mod_command = 0;
	map = int_map();
	while((rd = get_next_line(fd, &line)))
	{
		if (rd == -1)
			put_err("Not read file");
		ft_putendl(line);
		if (mod_command == 1 && (ft_strequ(line, "##start") || ft_strequ(line, "##end")))
			put_err("ERROR. more than one command line ##start or ##end in a row");
		if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
			mod_command = (ft_strequ(line, "##start")) ? START : END;
		else if (line[0] != '#')
		{
			parsing_line(line, map, mod_command);
			mod_command = 0;
		}
	}
	if (!map->start || !map->end)
		put_err("ERROR.Not start or end");
	check_start_end_connected(map);
	del_free_point(map);
//	copy_points(map);
//	connected_points2(map);
	connected_points(map);
	print_arr(map);
	if (line)
		free(line);
	return (map);
}