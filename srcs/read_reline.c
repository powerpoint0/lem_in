/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_reline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:29:09 by cjoaquin          #+#    #+#             */
/*   Updated: 2020/11/13 20:29:12 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_sline		*add_sline(t_data *map, t_point *p1, t_point *p2, int weight)
{
	if (!map->slines)
	{
		map->slines = new_sline(p1, p2, weight);
		map->last_slines = map->slines;
	}
	else
	{
		map->last_slines->next = new_sline(p1, p2, weight);
		map->last_slines = map->last_slines->next;
	}
	return (map->slines);
}

int			sline_start(t_data *map, t_line *line)
{
	t_point	*first0;
	t_point	*next1;
	t_point	*next2;

	first0 = map->start;
	next1 = get_point(map, line->num_next, 1);
	next2 = next1->next;
	add_sline(map, first0, next1, 1);
	if (next1 == map->end)
	{
		add_sline(map, next1, first0, 1);
		return (2);
	}
	else
	{
		add_sline(map, next1, next2, 0);
		add_sline(map, next2, first0, 1);
	}
	return (3);
}

int			sline_end(t_data *map, t_line *line)
{
	t_point	*first1;
	t_point	*first2;
	t_point	*next0;

	first1 = get_point(map, line->num_first, 1);
	first2 = first1->next;
	next0 = map->end;
	add_sline(map, first1, first2, 0);
	add_sline(map, first2, next0, 1);
	add_sline(map, next0, first1, 1);
	return (3);
}

int			sline_body(t_data *map, t_line *line)
{
	t_point	*first1;
	t_point	*first2;
	t_point	*next1;
	t_point	*next2;

	first1 = get_point(map, line->num_first, 1);
	first2 = first1->next;
	next1 = get_point(map, line->num_next, 1);
	next2 = next1->next;
	add_sline(map, first1, first2, 0);
	add_sline(map, first2, next1, 1);
	add_sline(map, next1, next2, 0);
	add_sline(map, next2, first1, 1);
	return (4);
}

t_sline		*set_slines(t_data *map)
{
	t_line	*line;
	int		num_of_edges;

	num_of_edges = 0;
	line = map->lines;
	while (line)
	{
		if (line->num_first == map->end->num)
			line_swap(line);
		if (line->num_first == map->start->num)
			num_of_edges += sline_start(map, line);
		else if (line->num_next == map->end->num)
			num_of_edges += sline_end(map, line);
		else
			num_of_edges += sline_body(map, line);
		line = line->next;
	}
	map->num_of_edges = num_of_edges;
	return (map->slines);
}
