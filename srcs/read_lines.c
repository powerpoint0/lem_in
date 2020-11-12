#include "lem-in.h"

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

t_sline	*new_sline(t_point *p1, t_point *p2, int weight)
{
	t_sline	*new;

	if (!(new = (t_sline*)ft_memalloc(sizeof(t_sline))))
		put_err("ERROR.No memory for malloc");
	new->in = p1;
	new->tmp_in = new->in;
	new->out = p2;
	new->weight = weight;
	new->next = NULL;
	return (new);
}

t_line	*new_line(char **str)
{
	t_line	*new;

	if (!(new = (t_line*)ft_memalloc(sizeof(t_line))))
		put_err("ERROR.No memory for malloc");
	new->p_first = str[0];
	new->p_next = str[1];
	new->next = NULL;
	return (new);
}

void	free_line(t_line	*line)
{
	if (line)
	{
		free(line->p_first);
		free(line->p_next);
	}
	free(line);
}

int		add_line(char **str, t_data *map)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	if (i != 2)
		put_err("ERROR.Invalid line");
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
	free(str);
	return (1);
}


void	copy_one_point2(t_point *point)
{
	t_point	*new;

	if (!(new = (t_point*)ft_memalloc(sizeof(t_point))))
		put_err("ERROR.No memory for malloc");
	ft_memcpy(new, point, sizeof(t_point));
	new->snum = point->snum + 1;
	new->p = 2;
	new->next = point->next;
	point->next = new;
}


void	copy_points2(t_data *map)
{
	t_point	*point;

	point = map->last_points;
	if (point != map->start &&
		point != map->end)
	{
		copy_one_point2(point);
		map->last_points = point->next;
	}
}

int		ft_check_num_ants(char *str)
{
	if(*str == '0')
		put_err("ERROR.Invalid num of ants");
	while(*str)
		if(!ft_isdigit(*str++))
			put_err("ERROR.Invalid num of ants");
	return(0);
}

void	ft_check_extra_symbols_in_line(char *str)
{
	int space;
	int minus;
	int tab;

	space = 0;
	minus = 0;
	tab = 0;
	if(str[0] == 'L')
		put_err("ERROR.Invalid name of point: L");
	while(*str)
	{
		if(*str == ' ')
			space++;
		else if(*str == '-')
			minus++;
		else if(*str == '\t')
			tab++;
		++str;
	}
	if(!((space == 2  && !minus && !tab) || (!space && minus == 1 && !tab)))
		put_err("ERROR.Invalid line: extra symbols in the line");
}

void		parsing_line(char *str, t_data *map, int mod_command)
{
	static int flag;

	if (map->num_ants == -1)
	{
		ft_check_num_ants(str);
		map->num_ants = ft_atoi_check(str);
		flag = POINTS;
	}
	else if (ft_find_count(str, ' ') != -1 && flag == POINTS)
	{
		ft_check_extra_symbols_in_line(str);
		add_point(ft_strsplit(str, ' '), map, mod_command);
		copy_points2(map);
	}
	else if (ft_find_count(str, '-') != -1)
	{
		ft_check_extra_symbols_in_line(str);
		add_line(ft_strsplit(str, '-'), map);
		flag = LINES;
	}
	else
		put_err("ERROR.Empty or invalid line");
}