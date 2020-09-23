/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 19:57:26 by dfigg             #+#    #+#             */
/*   Updated: 2019/09/20 19:51:53 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*ts1;
	char	*ts2;
	size_t	count;

	ts1 = (char *)s1;
	ts2 = (char *)s2;
	if (ts1 == ts2 || n == 0)
		return (0);
	count = 0;
	while (count < n)
	{
		if (ts1[count] != ts2[count])
			return ((unsigned char)ts1[count] - (unsigned char)ts2[count]);
		count++;
	}
	return (0);
}
