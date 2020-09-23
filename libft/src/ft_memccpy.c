/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 19:38:31 by dfigg             #+#    #+#             */
/*   Updated: 2019/09/16 19:42:25 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	count;
	char	*str_dest;
	char	*str_src;

	if (dest == src)
		return (dest);
	str_dest = (char *)dest;
	str_src = (char *)src;
	count = 0;
	while (count < n)
	{
		str_dest[count] = str_src[count];
		if (str_dest[count] == (char)c)
			return ((void *)&str_dest[count + 1]);
		count++;
	}
	return (NULL);
}
