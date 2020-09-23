/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:53:04 by dfigg             #+#    #+#             */
/*   Updated: 2019/09/21 17:56:50 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*t_str;
	char	*rez;

	if (!s)
		return (NULL);
	rez = ft_strnew(len);
	if (rez == NULL)
		return (NULL);
	t_str = (char*)s;
	i = 0;
	while (i < len)
	{
		rez[i] = t_str[start + i];
		i++;
	}
	rez[i] = '\0';
	return (rez);
}
