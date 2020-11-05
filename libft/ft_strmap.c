/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 02:46:18 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/20 21:32:03 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*ptr;
	size_t	len;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (!(ptr = (char *)malloc(sizeof(*ptr) * (len + 1))))
		return (NULL);
	else
	{
		while (s[i])
		{
			ptr[i] = f(s[i]);
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}
