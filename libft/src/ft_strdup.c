/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:51:29 by dfigg             #+#    #+#             */
/*   Updated: 2019/09/18 20:16:25 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*tmp;
	int		i;
	char	*src;

	src = (char*)s;
	tmp = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		tmp[i] = src[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
