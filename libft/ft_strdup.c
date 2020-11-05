/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 15:43:19 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/19 05:33:49 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*t;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s1[i])
	{
		len++;
		i++;
	}
	if (!(t = (char *)malloc(sizeof(*t) * (len + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		t[i] = s1[i];
		i++;
	}
	t[i] = '\0';
	return (t);
}
