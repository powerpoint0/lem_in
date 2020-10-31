#include <stdio.h>
#include "lem_in.h"
#define INF 1000000

int g_num = 0;

void printf1(char *str, char *name,int close1, char *name2,  int close2)
{
	if (g_num != 1)
		return;
	printf(str, name,close1, name2,  close2);
}

void	ft_init_points(t_data *map)
{
	map->start->cost = 0;
	map->end->prev_room_path = NULL;
	while (map->points)
	{
		//else if (!map->points->in_path)
		if (map->points != map->start)
			map->points->cost = INF;
		map->points = map->points->next;
	}
	map->end->in_path = 0;
	map->points = map->start;
}

int		ft_how_much_edges(t_sline *slines)
{
	int i;

	i = 0;
	t_sline *header;
	header = slines;
	while(slines)
	{
		i++;
		slines = slines->next;
	}
	slines = header;
	return(i);
}

int		ft_bellman_ford_deep(t_sline *slines, t_point *start)
{
	t_sline *header;
	header = slines;
	int k;

	k = 0;
	while(slines)
	{
		if(slines->out != start && (slines->out->cost > slines->in->cost + slines->weight))
		{
			k++;
			slines->out->cost = slines->in->cost + slines->weight;
			slines->out->prev_room_path = slines->in;
			//slines = header;
			//return(k);
		}
		slines = slines->next;
	}
	slines = header;
	return(k);
}

int		ft_bellman_ford(t_data *map)
{
	int num_of_edges;
	int iter = 0;

	num_of_edges = 0;
	ft_init_points(map);
	num_of_edges = ft_how_much_edges(map->slines);
	while (iter < num_of_edges)
	{
		if (!ft_bellman_ford_deep(map->slines, map->start))
			iter = num_of_edges;
		iter++;
	}
	//ft_bellman_ford_deep(map->slines,map->start);
//	if (ft_bellman_ford_deep(map->slines,map->start))               // - cycle
//		put_err("ERROR.Bellman-Ford.graph has negative cycle");
	if(!map->end->prev_room_path)
		return(-1);
	return(0);
}
