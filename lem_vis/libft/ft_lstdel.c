/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 21:01:32 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/21 22:17:21 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *temp;
	t_list *tempn;

	temp = *alst;
	while (temp != NULL)
	{
		tempn = temp->next;
		del(temp->content, temp->content_size);
		free(temp);
		temp = tempn;
	}
	*alst = NULL;
}
