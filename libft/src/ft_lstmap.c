/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 20:42:50 by dfigg             #+#    #+#             */
/*   Updated: 2019/11/11 20:57:52 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*new;

	if (lst == NULL)
		return (NULL);
	if (!(tmp = f(lst)))
	{
		free(tmp);
		return (NULL);
	}
	new = tmp;
	while (lst->next)
	{
		if (!(tmp->next = f(lst->next)))
		{
			free(tmp->next);
			return (NULL);
		}
		lst = lst->next;
		tmp = tmp->next;
	}
	return (new);
}
