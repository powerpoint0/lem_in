#include "lem_in.h"

void ft_clean_close(t_data *map)
{
	t_point *header;

	header = map->points;
	while(map->points->next)
	{
		if(map->points->close == 1)
			map->points->close = 0;
		map->points = map->points->next;
	}
	map->points->close = 0;
	map->points = header;
}
int		ft_bfs(t_data *map)
{
	t_point **queue;
	t_point *current;
	int queue_p;
	int i;
	int qp2;
	qp2 = 1;

	if (!(queue = (t_point **) ft_memalloc(sizeof(t_point *) * (map->last_points->num + 1))))
		put_err("Init.there is no memory for queue");
	ft_clean_close(map);
	queue[0] = map->start;
	map->start->bfs_level = 0;
	map->end->bfs_level = 0;
	map->start->close = 1;
	queue_p = 0;
	while (queue_p < qp2) {
		i = 0;
		current = queue[queue_p];

		while (current->arr_lines[i]) {
			if (!current->arr_lines[i]->close) {
				current->arr_lines[i]->bfs_level = current->bfs_level + 1;
				current->arr_lines[i]->prev_room_path = current;
			}
			if (current->close != 2)
				current->close = 1;
			if (current->arr_lines[i] == map->end)
				current->arr_lines[i]->close = 1;
			if (!current->arr_lines[i]->close)
				queue[qp2++] = current->arr_lines[i];
			i++;
		}
		queue_p++;
	}
	if (!map->end->bfs_level)
		return (-1);
	return (0);
}