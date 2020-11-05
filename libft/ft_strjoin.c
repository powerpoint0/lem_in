/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 04:09:33 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/20 22:19:20 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *ptr;

	if (!s1 || !s2)
		return (NULL);
	if (!(ptr = ft_strnew(ft_strlen((char*)s1) + ft_strlen((char*)s2))))
		return (NULL);
	else
	{
		ft_strcpy(ptr, s1);
		ft_strcat(ptr, s2);
		return (ptr);
	}
}
