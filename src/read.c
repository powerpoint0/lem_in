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

t_point	*new_point(char **str, int mod_command)
{
	t_point	*new;

	if (!(new = (t_point*)ft_memalloc(sizeof(t_point))))
		put_err("Init.Not creat point");
	new->name = str[0];
	new->x = ft_atoi_check(str[1]);
	new->y = ft_atoi_check(str[2]);
	new->st_end = mod_command;
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
	t_point	*header;

	header = map->points;
	if (!map->points)
	{
		map->points = new_point(str, mod_command);
	}
	else
	{
		while (map->points->next != NULL)
			map->points = map->points->next;
		map->points->next = new_point(str, mod_command);
		map->points = header;
	}
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

int		add_line(char **str, t_data *map)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	if (i != 2)
		return (0);
	t_line	*header;

	header = map->lines;
	if (!map->lines)
	{
		map->lines = new_line(str);
	}
	else
	{
		while (map->lines->next != NULL)
			map->lines = map->lines->next;
		map->lines->next = new_line(str);
		map->lines = header;
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

int 	check_line(t_data *map)
{
	t_point	*point_header;
	t_line	*line_header;
	int		ok;

	line_header = map->lines;
	while(map->lines)
	{
		ok = 0;
		point_header = map->points;
		while(map->points)
		{
			if (ft_strequ(map->lines->p_first, map->points->name))
				ok++;
			if (ft_strequ(map->lines->p_next, map->points->name))
				ok++;
			map->points = map->points->next;
		}
		map->points = point_header;
		if (ok == 2)
			map->lines = map->lines->next;
		else
			put_err("Not valid point in the line");
	}
	map->lines = line_header;
	return (1);
}

int 	check_duplicate_point(t_data *map)
{
	int		count;
	t_point	*header;
	t_point	*tmp;

	header = map->points;
	tmp = map->points;
	while (tmp)
	{
		count = 0;
		while(map->points)
		{
			if (ft_strequ(tmp->name, map->points->name))
				count++;
			map->points = map->points->next;
		}
		if (count > 1)
			put_err("Duplicate error");
		map->points = header;
		tmp = tmp->next;
	}
	return (1);
}

int 	check_point(t_data *map)
{
	check_duplicate_point(map);
	check_line(map);
	return (0);
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
	check_point(map);
	if (line)
		free(line);
	return (map);
}
