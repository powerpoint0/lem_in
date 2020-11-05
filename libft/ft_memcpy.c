/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:45:31 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/19 05:30:56 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*p;
	const unsigned char *p2;

	if (n == 0)
		return (dst);
	if ((unsigned char*)dst == 0 && (unsigned char*)src == 0)
		return (dst);
	p = (unsigned char*)dst;
	p2 = (unsigned char*)src;
	while (n--)
		*p++ = *p2++;
	return (dst);
}
