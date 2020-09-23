/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 18:35:29 by dfigg             #+#    #+#             */
/*   Updated: 2019/09/20 19:26:11 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	count;
	char	*str_dest;
	char	*str_src;

	if (dest == src)
		return (dest);
	str_dest = (char *)dest;
	str_src = (char *)src;
	if (dest < src)
	{
		count = 0;
		while (count++ < n)
			str_dest[count - 1] = str_src[count - 1];
	}
	if (dest > src)
	{
		while (n--)
			str_dest[n] = str_src[n];
	}
	return (dest);
}
