/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 01:34:02 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/19 05:36:14 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t h;

	i = 0;
	h = 0;
	if (n == 0)
		return (s1);
	if (*s2 == '\0')
		return (s1);
	while (s1[i])
		i++;
	while (h < n && s2[h])
	{
		s1[i] = s2[h];
		h++;
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
