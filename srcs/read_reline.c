#include "lem-in.h"

t_sline	*add_sline(t_data *map, t_point *p1, t_point *p2, int weight)
{
	t_sline	*header;

	if (!map->slines) {
		header = new_sline(p1, p2, weight);
		//map->last_slines = header;
	}
	else
	{
		header = map->slines;
		while (map->slines->next)
			map->slines = map->slines->next;
		map->slines->next = new_sline(p1, p2, weight);
		//map->last_slines->next = new_sline(p1, p2, weight);
	}
	return (header);
}

void	sline_start(t_data *map, t_line *line)
{
	map->slines = add_sline(map, get_point(map, line->num_first, 0),
						get_point(map, line->num_next, 1), 1);
	map->slines = add_sline(map, get_point(map, line->num_next, 1),
						get_point(map, line->num_next, 2), 0);
	map->slines = add_sline(map, get_point(map, line->num_next, 2),
						get_point(map, line->num_first, 0), 1);
	//map->last_slines = map->last_slines->next;
}

void	sline_body(t_data *map, t_line *line)
{
	map->slines = add_sline(map, get_point(map, line->num_first, 1),
						get_point(map, line->num_first, 2), 0);
	map->slines = add_sline(map, get_point(map, line->num_first, 2),
						get_point(map, line->num_next, 0), 1);
	map->slines = add_sline(map, get_point(map, line->num_next, 0),
						get_point(map, line->num_first, 1), 1);
	//map->last_slines = map->last_slines->next;
}

void	sline_end(t_data *map, t_line *line)
{
	map->slines = add_sline(map, get_point(map, line->num_first, 1),
						get_point(map, line->num_first, 2), 0);
	map->slines = add_sline(map, get_point(map, line->num_first, 2),
						get_point(map, line->num_next, 1), 1);
	map->slines = add_sline(map, get_point(map, line->num_next, 1),
						get_point(map, line->num_next, 2), 0);
	map->slines = add_sline(map, get_point(map, line->num_next, 2),
						get_point(map, line->num_first, 1), 1);
	//map->last_slines = map->last_slines->next;
}

t_sline	*set_sline(t_data *map)
{
	t_line	*line;

	line = map->lines;
	while (line)
	{
		if (line->num_first == map->start->num)
			sline_start(map, line);
		else if (line->num_next == map->end->num)
			sline_body(map, line);
		else
			sline_end(map, line);
		line = line->next;
	}
	return (map->slines);
}
