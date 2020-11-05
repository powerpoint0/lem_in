#include "lem-in.h"

int		ft_bellman_ford_deep(t_sline *slines, t_point *start)
{
	int k;

	k = 0;
	while(slines)
	{
		if(slines->out != start && slines->close != CLOSE &&
		(slines->out->cost > slines->in->cost + slines->weight))
		{
			k++;
			slines->out->cost = slines->in->cost + slines->weight;
			slines->out->prev_room_path = slines->in;
		}
		slines = slines->next;
	}
	return(k);
}

int		ft_bellman_ford(t_data *map)
{
	int iter = 0;

	ft_init_points(map);
	while (iter < map->num_of_edges)
	{
		if (!ft_bellman_ford_deep(map->slines, map->start))
			iter = map->num_of_edges;
		iter++;
	}
	if(!map->end->prev_room_path)
		return(-1);
	return(0);
}
