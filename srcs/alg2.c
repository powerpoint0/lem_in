#include "lem-in.h"

int	ft_change_edge(t_sline *slines)
{
	t_point *tmp;
	int		common_edges;

	common_edges = 0;
	while(slines)
	{
		if(slines->out->in_path && slines->in->in_path
		   && slines->out->prev_room_path == slines->in && slines->close != CLOSE)
		{
			if (slines->weight == -1)
			{
				slines->close = CLOSE;
				common_edges = 1;
			}
			tmp = slines->in;
			slines->in = slines->out;
			slines->out = tmp;
			slines->weight *= -1;
		}
		slines = slines->next;
	}
	return(common_edges);
}

t_path*		ft_create_path(t_data *map)
{
	t_path *path;
	t_path *new_point;
	t_point *point;

	path = NULL;
	point = map->end;
	while(point)
	{
		if (!(new_point = (t_path *) ft_memalloc(sizeof(t_path))))
			put_err("Init.there is no memory for path");
		if(path)
			path->prev = new_point;
		new_point->next = path;
		new_point->points = point;
		new_point->points->in_path = 2;
		path = new_point;
		if(path->points == map->start)
			break;
		point = point->prev_room_path;
	}
	return (path);
}

int		ft_how_much_edges(t_sline *slines)
{
	int i;

	i = 0;
	while(slines)
	{
		i++;
		slines = slines->next;
	}
	return(i);
}

void ft_free_path(t_path **path)
{
	t_path *root;
	t_path *tmp;

	root = *path;
	while (root)
	{
		tmp = root;
		root = root->next;
		free(tmp);
	}
	*path = NULL;
}

void ft_free_paths(t_path **paths)
{
	int i;

	i = 0;
	if(!paths)
		return;
	while(paths[i])
	{
		ft_free_path(&paths[i]);
		i++;
	}
}

//void ft_free_paths(t_path **paths)
//{
//	int i;
//	t_path *tmp;
//	t_path *path_point;
//
//	i = 0;
//	if(!paths)
//		return;
//	while(paths[i])
//	{
//		path_point = paths[i];
//		while(path_point)
//		{
//			tmp = path_point;
//			path_point = path_point->next;
//			free(tmp);
//		}
//		paths[i] = NULL;
//		i++;
//	}
//}

