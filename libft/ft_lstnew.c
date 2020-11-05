/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:15:19 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/21 20:52:17 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*elem;

	if (!(elem = (t_list *)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		elem->content_size = 0;
		elem->content = NULL;
	}
	else
	{
		if (!(elem->content = ft_memalloc(content_size)))
		{
			free(elem);
			return (NULL);
		}
		ft_memcpy(elem->content, content, content_size);
		elem->content_size = content_size;
	}
	elem->next = NULL;
	return (elem);
}
