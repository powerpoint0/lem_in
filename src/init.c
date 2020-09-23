#include "lem_in.h"

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