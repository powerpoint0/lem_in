/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrevers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:41:58 by dfigg             #+#    #+#             */
/*   Updated: 2019/11/12 19:18:32 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstrevers(t_list *lst)
{
	t_list	*rev;
	t_list	*tmp;

	if (!lst)
		return (NULL);
	rev = ft_lstnew(lst->content, lst->content_size);
	while (lst->next)
	{
		lst = lst->next;
		tmp = ft_lstnew(lst->content, lst->content_size);
		ft_lstadd(&rev, tmp);
	}
	return (tmp);
}
