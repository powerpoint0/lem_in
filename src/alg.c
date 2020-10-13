#include "lem_in.h"

int		ft_letGoAnts(t_path **paths)
{
	return(0);
}

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

t_path 		**ft_realloc(t_path **paths, int str)
{
//	int	**copy;
//	int j;
//
//	j = 0;
//	copy = paths;
//	if (!(paths = (int **)ft_memalloc(sizeof(int *) * str)))
//		put_err("Init.there is no memory for paths");
//	while(j <= copy[0][1])
//	{
//		ft_memcpy(paths[j], copy[j], sizeof(int)* (copy[j][0]+1));
//		j++;
//	}
//	ft_free_int(copy);
	return(paths);
}

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
			new_point->next = path;
			if(path->points->prev_room_path)
				new_point->points = path->points->prev_room_path;
			else
				new_point->points = map->start;
			new_point->last_points = path->last_points;
			new_point->len = map->end->bfs_level;
			path = new_point;
			if(path->points == map->start)
				break;
			//path->points->close = 2;
			ft_change_edge(path, map);
		}
	}
	return (path);
}

int	alg(t_data *map)
{
	t_path **paths;
	int check;
	int i;
	int strings;

	strings = 21;
	i = 0;
	if (!(paths = (t_path **)ft_memalloc(sizeof(t_path *) * strings)))
		put_err("ERROR.Init.there is no memory for paths");
	//printf("end %d\n",map->end->bfs_level);
	while (!(check = ft_bfs(map)))
	{
		if(i >= strings)
		{
			strings += 10;
			paths = ft_realloc(paths, strings);
		}
		paths[i] = ft_create_path(paths[i], map);
		i++;
	}
	if(check < 0 && !*paths)
		put_err("ERROR.There is no path between START and END");
	ft_letGoAnts(paths);
	return (0);
}