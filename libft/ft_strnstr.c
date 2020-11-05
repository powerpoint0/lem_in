/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 22:26:26 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/22 01:31:33 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*temp;
	size_t	max;
	size_t	i;

	i = 0;
	max = ft_strlen(needle);
	if (haystack == needle)
		return ((char*)haystack);
	if (*needle == '\0')
		return ((char*)haystack);
	if (len == 0)
		return (NULL);
	temp = (char*)haystack;
	while (*temp && i + max <= len)
	{
		if (ft_strncmp(temp, needle, max) == 0)
			return (temp);
		i++;
		temp++;
	}
	return (NULL);
}
