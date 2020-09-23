/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:17:24 by dfigg             #+#    #+#             */
/*   Updated: 2019/09/18 19:32:45 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*str_s;

	str_s = (char *)s;
	len = ft_strlen(str_s);
	while (len >= 0)
	{
		if (str_s[len] == (char)c)
			return ((char *)str_s + len);
		len--;
	}
	return (NULL);
}
