/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 23:41:08 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/22 00:13:20 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *first;
	t_list *prev;
	t_list *new;

	first = NULL;
	if (lst)
	{
		first = ft_lstnew(lst->content, lst->content_size);
		first = f(first);
		prev = first;
		lst = lst->next;
	}
	while (lst)
	{
		new = ft_lstnew(lst->content, lst->content_size);
		if (new == NULL)
			return (NULL);
		new = f(new);
		prev->next = new;
		prev = new;
		lst = lst->next;
	}
	return (first);
}
