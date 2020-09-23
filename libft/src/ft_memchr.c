/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 19:45:14 by dfigg             #+#    #+#             */
/*   Updated: 2019/09/20 19:31:11 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str_s;
	size_t	count;

	str_s = (char *)s;
	count = 0;
	while (count < n)
	{
		if (str_s[count] == (char)c)
			return ((void *)s + count);
		count++;
	}
	return (NULL);
}
