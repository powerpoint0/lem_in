#include "lem-in.h"

int is_repeat_room(t_path **paths, t_path *room)
{
	int repeates = 0;
	t_path *path;
	int i = 0;

	while(paths[i])
	{
		path = paths[i];
		while(path)
		{
			if (path->points == room->points)
				repeates++;
			if (repeates > 1)
				printf("%s\n", room->points->name);
			path = path->next;
		}
		i++;
	}
	if (repeates > 1)
		return (1);
	return(0);
}

void ft_check_repeat_rooms(t_path **paths)
{
	t_path *path;
	int i = 0;

	while(paths[i])
	{
		path = paths[i]->next;
		while(path->next)
		{
			if (is_repeat_room(paths, path))
			{
				print_paths(paths);
				printf("пути повторяются!\n");
//				exit(0);
				return;
			}
			path = path->next;
		}
		i++;
	}
	printf("пути не повторяются!\n");
}

int ft_len_of_path(t_path *paths)
{
	int len = 0;
	while(paths)
	{
		len++;
		paths = paths->next;
	}
	return(len/2 + 1);
}

void print_paths(t_path **paths)
{
	t_path *path;
	int i;

	i = 0;
	while (paths[i])
	{

		path = paths[i];

		printf("%d ", ft_len_of_path(paths[i]));
		while (path)
		{
			printf("%s%d ", path->points->name,  path->points->p);
			path = path->next;
		}
		printf("\n");
		i++;
	}
}

void	print_sline(t_data *map)
{
	t_sline	*line;

	line = map->slines;
	while (line)
	{
		printf("%s(%d)cost%d - %s(%d)cost%d [%d] close=%d\n", line->in->name, line->in->p, line->in->cost,
			   line->out->name, line->out->p, line->out->cost, line->weight, line->close);
		line = line->next;
	}
}
