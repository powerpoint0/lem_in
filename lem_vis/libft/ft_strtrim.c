/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 05:17:18 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/20 21:41:56 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*ptr;
	size_t	n;
	size_t	k;

	k = 0;
	n = 0;
	if (!s)
		return (NULL);
	if (s[n] == '\0')
		return ((char*)s);
	while ((s[n] == ' ' || s[n] == '\n' || s[n] == '\t') && s[n])
		n++;
	if (s[n] == '\0')
		return (ft_strnew(0));
	while (s[k])
		k++;
	k--;
	while (s[k] == ' ' || s[k] == '\n' || s[k] == '\t')
		k--;
	if (!(ptr = ft_strnew(k - n + 1)))
		return (NULL);
	ft_strncpy(ptr, &s[n], k - n + 1);
	return (ptr);
}
