/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:16:33 by dfigg             #+#    #+#             */
/*   Updated: 2019/09/20 18:59:44 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *s1, const char *s2, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	result;
	char	*src;

	src = (char *)s2;
	i = 0;
	j = 0;
	result = ft_strlen(src);
	while (s1[i] && i < size)
		i++;
	if (size > 0)
	{
		while (src[j] && i < size - 1)
			s1[i++] = src[j++];
	}
	if (j > 0)
	{
		s1[i] = '\0';
		return (result + i - j);
	}
	return (result + i);
}
