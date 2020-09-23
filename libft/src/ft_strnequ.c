/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strenqu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:44:19 by dfigg             #+#    #+#             */
/*   Updated: 2019/09/21 17:28:10 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	char	*s1t;
	char	*s2t;

	s1t = (char*)s1;
	s2t = (char*)s2;
	if (s1t && s2t)
	{
		if (ft_strncmp(s1t, s2t, n) == 0)
			return (1);
		else
			return (0);
	}
	return (0);
}
