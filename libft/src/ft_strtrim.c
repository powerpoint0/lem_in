/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:17:25 by dfigg             #+#    #+#             */
/*   Updated: 2019/09/28 09:31:47 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		st;
	int		len;
	char	*strnew;
	char	*tstr;

	tstr = (char*)(s);
	if (!tstr)
		return (NULL);
	st = 0;
	while (tstr && (tstr[st] == ' ' || tstr[st] == '\n' || tstr[st] == '\t'))
		st++;
	len = ft_strlen(tstr) - 1;
	while (tstr && (tstr[len] == ' ' || tstr[len] == '\n' || tstr[len] == '\t'))
		len--;
	len++;
	if (st >= len)
		return (ft_strnew(0));
	if (!(strnew = ft_memalloc(len - st)))
		return (NULL);
	strnew = ft_strsub(tstr, st, (len - st));
	return (strnew);
}
