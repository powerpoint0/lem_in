#include "lem_in.h"
/*
int		ft_letGoAnts(t_path **paths)
{
	return(0);
}
*/
//void	ft_free_int(int **copy)
//{
//	int j;
//	int str;
//
//	if(!copy)
//		return;
//	str = copy[0][1];
//	j = 0;
//	while(j <= str)
//	{
//		free(copy[j]);
//		j++;
//	}
//	free(copy);
//}

void ft_change_edge(t_path *path, t_data *map)
{
	int i = 0;

	while (path->points->arr_lines[i] != path->next->points)
		i++;
	//path->points->check[i + 1] = (path->points->check[i + 1] == 1) ? -1 : 0;
	path->points->check[i + 1] = 0;
}

t_path *		ft_create_path(t_path *path, t_data *map)
{
	t_path *new_point;

	while(map->start)
	{

		if (!path)
		{
			if (!(path = (t_path *) ft_memalloc(sizeof(t_path))))
				put_err("Init.there is no memory for path");
			path->points = map->end;
			path->last_points = map->end;
			path->len = map->end->bfs_level;
		}
		else
		{
			if (!(new_point = (t_path *) ft_memalloc(sizeof(t_path))))
				put_err("Init.there is no memory for path");
			path->prev = new_point;
			new_point->next = path;
			if(path->points->prev_room_path2)
			{
				new_point->points = path->points->prev_room_path2;
				path->points->prev_room_path2 = NULL;
			}
			else if(path->points->prev_room_path)
				new_point->points = path->points->prev_room_path;
			else
				new_point->points = map->start;
			new_point->last_points = path->last_points;
			new_point->len = map->end->bfs_level;
			path = new_point;
			ft_change_edge(path, map);
			if(path->points == map->start)
				break;
			path->points->in_path =1;
			path->points->close = 2;
		}
	}
	return (path);
}


void print_paths(t_path **paths) {
	t_path *path;
	int i;

	i = 0;

	while (paths[i])
	{
		path = paths[i];
		while (path)
		{
			printf("%s%d ", path->points->name,  path->points->p);
			path = path->next;
		}
		printf("\n");
		i++;
	}
}

int	alg(t_data *map)
{
	t_path **paths;
	int check;
	int i;

	i = 0;
	if (!(paths = (t_path **)ft_memalloc(sizeof(t_path *) * (map->start->check[0] + 1))))
		put_err("ERROR.Init.there is no memory for paths");
	while (!(check = ft_bfs(map)))
	{
		paths[i] = ft_create_path(paths[i], map);
		i++;
	}
	if(check < 0 && !*paths)
		put_err("ERROR.There is no path between START and END");
	print_paths(paths);
	ft_letGoAnts(paths, map);
	return (0);
}