/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 04:40:24 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/19 05:36:48 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return (&((char*)s)[i]);
	else
		return (NULL);
}
