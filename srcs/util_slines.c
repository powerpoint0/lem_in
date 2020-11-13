/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_slines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:29:49 by cjoaquin          #+#    #+#             */
/*   Updated: 2020/11/13 20:29:52 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_sline		*new_sline(t_point *p1, t_point *p2, int weight)
{
	t_sline	*new;

	if (!(new = (t_sline*)ft_memalloc(sizeof(t_sline))))
		put_err("ERROR.No memory for malloc");
	new->in = p1;
	new->tmp_in = new->in;
	new->out = p2;
	new->weight = weight;
	new->next = NULL;
	return (new);
}

void		line_swap(t_line *line)
{
	char	*tmp;
	int		tnum;

	tmp = line->p_first;
	line->p_first = line->p_next;
	line->p_next = tmp;
	tnum = line->num_first;
	line->num_first = line->num_next;
	line->num_next = tnum;
}
