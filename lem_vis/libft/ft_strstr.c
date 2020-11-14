/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 05:18:03 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/16 22:25:38 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	len;
	char	*temp;

	temp = (char*)haystack;
	if (*needle == '\0')
		return ((char*)haystack);
	len = ft_strlen(needle);
	while (*temp)
	{
		if (ft_strncmp(temp, needle, len) == 0)
			return (temp);
		temp++;
	}
	return (NULL);
}
