/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:54:27 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/19 05:31:39 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	if (src == NULL && dst == NULL)
		return (dst);
	else if (src == dst)
		return (dst);
	else if (src < dst)
	{
		while (len--)
			((unsigned char*)dst)[len] = ((unsigned char*)src)[len];
		return (dst);
	}
	else if (src > dst)
	{
		i = 0;
		while (i < len)
		{
			((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
			i++;
		}
	}
	return (dst);
}
