#include "lem-in.h"

t_point	*get_point(t_data *map, int num, int p)
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

t_point	*new_point(char **str, int num)
{
	t_point	*new;

	if (!(new = (t_point*)ft_memalloc(sizeof(t_point))))
		put_err("Init.Not create point");
	new->num = num;
	new->snum = -1;
	new->ant_num = -1;
	new->p = 1;
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
		map->last_points = map->last_points->next;
	}
	if (mod_command == START)
		map->start = map->last_points;
	if (mod_command == END)
		map->end = map->last_points;
//	free_str(str);
	return (1);
}

void	copy_one_point(t_point *point, int snum)
{
	t_point	*new;

	if (!(new = (t_point*)ft_memalloc(sizeof(t_point))))
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
