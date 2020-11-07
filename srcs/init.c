#include "lem-in.h"

t_data	*int_map(void)
{
	t_data	*map;

	if (!(map = (t_data*)ft_memalloc(sizeof(t_data))))
		put_err("Init.Not creat map");
	map->num_ants = -1;
	map->points = NULL;
	map->lines = NULL;
	return (map);
}

void ft_num_of_max_paths(t_data *map)
{
	int		i;
	t_sline *header;

	i = 0;
	header = map->slines;
	while(map->slines)
	{
		if(map->slines->in == map->start || map->slines->out == map->start)
			i++;
		map->slines = map->slines->next;
	}
	map->max_paths = i;
	map->slines = header;
}

t_path	**ft_init_paths(t_data *map)
{
	t_path	**paths;

	if (!(paths = (t_path **) ft_memalloc(sizeof(t_path *) * (map->max_paths + 1))))
		put_err("ERROR.Init.there is no memory for paths");
	return(paths);
}

void	ft_init_points(t_data *map)
{
	map->start->cost = 0;
	map->end->prev_room_path = NULL;
	while (map->points)
	{
		if (map->points != map->start)
			map->points->cost = INF;
		map->points->in_path = 0;
		map->points->prev_room_path = 0;
		map->points = map->points->next;
	}
	map->points = map->start;
}

void	ft_init_slines(t_sline *slines)
{
	while(slines)
	{
		if(slines->weight == -1 || slines->weight == 0)
		{
			slines->weight *= -1;
			if(slines->in != slines->tmp_in)
			{

				slines->out = slines->in;
				slines->in = slines->tmp_in;
			}
		}
		slines = slines->next;
	}
}