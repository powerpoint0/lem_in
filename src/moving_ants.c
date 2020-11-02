#include "lem_in.h"

int	add_ant(t_path *path, t_data *map, int ants)
{
	if (ants == 0)
		path->points->ant_num = -1;
	else
	{
		map->ants_count++;
		path->points->ant_num = map->ants_count;
		map->location = add_loc(map, path->points->name, path->points->ant_num);
		ants--;
	}
	return (ants);
}

t_loc	*set_new_loc(char *name, int num_ant)
{
	t_loc	*new;

	if (!(new = (t_loc*)ft_memalloc(sizeof(t_loc))))
		put_err("ERROR");
	new->name = ft_strdup(name);
	new->i = num_ant;
	new->next = NULL;
	return (new);
}

void	ins_loc(t_data *map, char *name, int num_ant)
{
	t_loc	*new;
	t_loc	*next;
	t_loc	*loc;

	loc = map->location;
	new = set_new_loc(name, num_ant);
	if (loc->i > num_ant)
	{
		next = loc;
		new->next = next;
		map->location = new;
	}
	else
	{
		while (loc->next && loc->next->i <= num_ant)
			loc = loc->next;
		if (!loc->next)
			loc->next = new;
		else if (loc->i < num_ant)
		{
			next = loc->next;
			loc->next = new;
			new->next = next;
		}
	}
}

t_loc	*add_loc(t_data *map, char *name, int num_ant)
{
	t_loc	*header;

	header = NULL;
	if (!map->location)
	{
		map->location = set_new_loc(name, num_ant);
		header = map->location;
	}
	else
	{
		header = map->location;
		ins_loc(map, name, num_ant);
//		while (map->location->next)
//			map->location = map->location->next;
//		map->location->next = set_new_loc(name, num_ant);
	}
	return (header);
}

void	move_by_path(t_path **paths, t_data *map, int *ants)
{
	int		i;
	t_path *path;

	i = 0;
	while (paths[i])
	{
		path = paths[i];
		while (path->points->num != map->end->num)
			path = path->next;
		while (path->prev)
		{
			if (path->points->num == map->end->num && path->points->ant_num != -1)
				map->ants_end++;
			if (path->prev->points->num != map->start->num)
			{
				path->points->ant_num = path->prev->points->ant_num;
				if (path->points->ant_num != -1)
					map->location = add_loc(map, path->points->name, path->points->ant_num);
			}
			else
				ants[i] = add_ant(path, map, ants[i]);
			path = path->prev;
		}
		i++;
	}
}

void	print_posicion(t_loc *location)
{
	t_loc *ploc;

	ploc = location;
	while (ploc)
	{
		write(1, "L", 1);
		ft_putnbr(ploc->i);
		write(1, "-", 1);
		ft_putstr(ploc->name);
		if (ploc->next)
			write(1, " ", 1);
		ploc = ploc->next;
	}
	write(1, "\n", 1);
}

int	get_num_path(t_path **paths)
{
	int	num;

	num = 0;
	while (paths[num])
		num++;
	return (num);
}

int	*set_ant_in_path(t_path **paths, t_data *map)
{
	int	*ant_in_path;
	int	size;
	int	i;
	int	count;

	size = get_num_path(paths);
	if(!(ant_in_path = (int*)ft_memalloc(sizeof(int) * size)))
		put_err("ERROR. ants problem");
	i = 0;
	count = 0;
	while (i < map->num_ants)
	{
		if (count == 0)
		{
			ant_in_path[count]++;
			count++;
		}
		else if (paths[count]->len < (ant_in_path[count - 1] + paths[count - 1]->len))
		{
			ant_in_path[count]++;
			count++;
		}
		else
		{
			count = 0;
			i--;
		}
		if (count == size)
			count = 0;
		i++;
	}
	return (ant_in_path);
}

void	prt_path(t_path **paths)
{
	int		i;
	t_path *path;

	i = 0;
	while (paths[i])
	{
		path = paths[i];
		while (path)
		{
			printf("%s%d\t", path->points->name, path->points->ant_num);
			path = path->next;
		}
		printf("\n");
		i++;
	}
}

void	del_locatin(t_data *map)
{
	t_loc	*del;

	while (map->location)
	{
		del = map->location;
		map->location = map->location->next;
		free(del);
		del = NULL;
	}

}

int iter_count(t_path **paths, t_data *map)
{
	int       i;
	int       count;
	int       *ants;
	i = 0;
	count = 0;
	ants = set_ant_in_path(paths, map);
	while (paths[i])
	{
		count += paths[i]->len + (ants[i] - 1);
		i++;
	}
	if (ants)
		free(ants);
	return (count);
}

int		ft_letGoAnts(t_path **paths, t_data *map)
{
	int		*ants;

	map->ants_end = 0;
	map->ants_count = 0;
	ants = set_ant_in_path(paths, map);
	while (map->ants_end != map->num_ants)
	{
		move_by_path(paths, map, ants);
//		prt_path(paths);
		print_posicion(map->location);
		del_locatin(map);
	}

//	add_ants(paths, map);
//	move_by_path(paths, map);

	if (ants)
		free(ants);
	return (0);
}