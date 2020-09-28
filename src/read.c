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
	if (i == 0 || rez > INT32_MAX)
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

t_point	*new_point(char **str, int mod_command, int num)
{
	t_point	*new;

	if (!(new = (t_point*)ft_memalloc(sizeof(t_point))))
		put_err("Init.Not create point");
	new->num = num;
	new->name = str[0];
	new->x = ft_atoi_check(str[1]);
	new->y = ft_atoi_check(str[2]);
	new->in_path = 0;
	new->next = NULL;
	return (new);
}

int		add_point(char **str, t_data *map, int mod_command)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	if (i != 3)
		return (0);
	if (!map->points)
	{
		map->points = new_point(str, mod_command, 0);
		map->last_points = map->points;
	}
	else
	{
		map->last_points->next = new_point(str, mod_command,
										   (map->last_points->num + 1));
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
		if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
			mod_command = (ft_strequ(line, "##start")) ? START : END;
		else if (line[0] != '#')
		{
			parsing_line(line, map, mod_command);
			mod_command = 0;
		}
	}
	if (line)
		free(line);
	return (map);
}