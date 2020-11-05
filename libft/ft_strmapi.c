/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 03:01:43 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/20 21:33:07 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
			ptr[i] = f(i, s[i]);
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}
