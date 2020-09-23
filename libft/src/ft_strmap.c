/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:19:32 by dfigg             #+#    #+#             */
/*   Updated: 2019/09/21 16:20:55 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*str_new;
	char	*str_tmp;

	str_tmp = (char*)s;
	if (!str_tmp)
		return (NULL);
	if (!(str_new = ft_strnew(ft_strlen(str_tmp))))
		return (NULL);
	i = 0;
	while (str_tmp[i])
	{
		str_new[i] = f(str_tmp[i]);
		i++;
	}
	str_new[i] = '\0';
	return (str_new);
}
