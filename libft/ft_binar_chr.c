/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binar_chr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 02:15:30 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/22 03:17:00 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_binar_chr(char *str, char item)
{
	int		low;
	int		high;
	int		mid;
	char	*guess;

	low = 0;
	high = ft_strlen((const char *)str);
	while (low <= high)
	{
		mid = (low + high) / 2;
		guess = &str[mid];
		if (*guess == item)
			return (&str[mid]);
		if (*guess > item)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return (NULL);
}
