/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_copy_n_free_paths.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:26:44 by cjoaquin          #+#    #+#             */
/*   Updated: 2020/11/13 20:26:48 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path		*ft_copy_in_best_one_path(t_path *path)
{
	t_path	*best_path;
	t_path	*header;
	t_path	*new_point;

	best_path = NULL;
	while (path)
	{
		if (!(new_point = (t_path *)ft_memalloc(sizeof(t_path))))
			put_err("ERROR.No memory for malloc");
		new_point->points = path->points;
		if (best_path)
		{
			new_point->prev = best_path;
			best_path->next = new_point;
		}
		else
			header = new_point;
		best_path = new_point;
		path = path->next;
	}
	best_path = header;
	return (best_path);
}

void		ft_copy_in_best_paths(t_path **paths, t_path **best_paths)
{
	int		i;

	i = 0;
	while (paths[i])
	{
		best_paths[i] = ft_copy_in_best_one_path(paths[i]);
		i++;
	}
	best_paths[0]->num_steps_in_paths = paths[0]->num_steps_in_paths;
}

void		ft_free_path(t_path **path)
{
	t_path	*root;
	t_path	*tmp;

	root = *path;
	while (root)
	{
		tmp = root;
		root = root->next;
		free(tmp);
	}
	*path = NULL;
}

void		ft_free_all_paths(t_path **paths)
{
	int i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
	{
		ft_free_path(&paths[i]);
		i++;
	}
}

void		ft_free_all_in_alg(t_path **paths, t_sline *slines)
{
	t_sline	*prev_slines;

	while (slines)
	{
		prev_slines = slines;
		slines = slines->next;
		free(prev_slines);
	}
	ft_free_all_paths(paths);
	if (paths)
		free(paths);
}
