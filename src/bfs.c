#include "lem_in.h"

void	ft_bfs(t_data *map)
{
	t_point **queue;
	t_point *current;
	int queue_p;
	int i;
	int lvl1;
	queue_p = 0;
	i = 0;

	if(!(queue = (t_point **)ft_memalloc(sizeof(t_point*)* (map->last_points->num + 1) )))
		put_err("Init.there is no memory for queue");
	queue[0] = map->start;
	map->start->bfs_level = 0;
	while(map->start->arr_lines[i] != NULL)
	{
		map->start->arr_lines[i]->bfs_level = 1;
		queue[queue_p++] = map->start->arr_lines[i++];
		lvl1 = i;
	}
	queue_p = 0;
	while(queue[queue_p])
	{
		i = 0;
		current = queue[queue_p];
		while(current->arr_lines[i] != NULL)
		{
			if((current->arr_lines[i]->bfs_level > current->bfs_level + 1) ||
					(!current->arr_lines[i]->bfs_level &&current->arr_lines[i] != map->start))
				current->arr_lines[i]->bfs_level = current->bfs_level + 1;
			current->close = 1;
			if(current->arr_lines[i] == map->end)
				current->arr_lines[i]->close = 1;
			if(!current->arr_lines[i]->close)
				queue[queue_p + lvl1] = current->arr_lines[i];
			i++;
		}
		queue_p++;
	}
}

