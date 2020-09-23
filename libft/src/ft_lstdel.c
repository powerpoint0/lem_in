/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:09:18 by dfigg             #+#    #+#             */
/*   Updated: 2019/11/05 19:05:59 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*prev;

	if (*alst && *del)
	{
		while (*alst != NULL)
		{
			prev = (*alst);
			(*alst) = (*alst)->next;
			del(prev->content, prev->content_size);
			free(prev);
			prev = NULL;
		}
	}
}
