#include "lem-in.h"
//	char *name;
//
//	if (!(name = (char *)ft_memalloc(sizeof(char) * ft_strlen(str[0]) + 1)))
//		put_err("Init.Not create point");

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
		put_err("Init.Not creat line");
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
		put_err("Init.Not creat line");
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
		put_err("Error!!!!!   !!!");
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
		put_err("ERROR. Copy point");
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


# define BEGIN 0
# define ANTS 1
# define POINTS 2
# define LINES 3

int		parsing_line(char *str, t_data *map, int mod_command)
{
	static int flag;

	if (map->num_ants == -1)
	{
		map->num_ants = ft_atoi_check(str);
		flag = POINTS;
	}
	else if (ft_find_count(str, ' ') != -1 && flag == POINTS)
	{
		add_point(ft_strsplit(str, ' '), map, mod_command);
		copy_points2(map);
	}
	else if (ft_find_count(str, '-') != -1)
	{
		add_line(ft_strsplit(str, '-'), map);
		flag = LINES;
	}
	return (1);
}