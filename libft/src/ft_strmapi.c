/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:22:23 by dfigg             #+#    #+#             */
/*   Updated: 2019/09/21 16:33:09 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str_new;
	char			*str_tmp;

	str_tmp = (char*)s;
	if (!str_tmp)
		return (NULL);
	if (!(str_new = (char *)ft_memalloc(ft_strlen(str_tmp) + 1)))
		return (NULL);
	i = 0;
	while (str_tmp[i])
	{
		str_new[i] = (*f)(i, str_tmp[i]);
		i++;
	}
	str_new[i] = '\0';
	return (str_new);
}
