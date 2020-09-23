/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 09:34:24 by dfigg             #+#    #+#             */
/*   Updated: 2019/09/20 19:04:01 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	count;
	char	*tmpb;

	tmpb = (char*)b;
	count = 0;
	while (count < len)
	{
		tmpb[count] = (char)c;
		count++;
	}
	return (b);
}
