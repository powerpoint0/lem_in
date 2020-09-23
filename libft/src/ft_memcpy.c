/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 19:17:28 by dfigg             #+#    #+#             */
/*   Updated: 2019/09/16 19:35:11 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t num)
{
	size_t	count;
	char	*str_dest;
	char	*str_src;

	if (dest == src)
		return (dest);
	str_dest = (char *)dest;
	str_src = (char *)src;
	count = 0;
	while (count < num)
	{
		str_dest[count] = str_src[count];
		count++;
	}
	return (dest);
}
