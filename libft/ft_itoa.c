/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 23:45:53 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/19 04:06:25 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_skolkocifr(int n)
{
	size_t	kolznak;

	kolznak = 1;
	if (n < 0)
		kolznak++;
	while (n /= 10)
		kolznak++;
	return (kolznak);
}

char			*ft_itoa(int n)
{
	char	*ptr;
	int		i;
	int		k;

	k = 0;
	if (!(ptr = ft_strnew(ft_skolkocifr(n))))
		return (NULL);
	i = -1000000000;
	if (n == 0)
	{
		ptr[0] = '0';
		return (ptr);
	}
	(n >= 0) ? (n *= -1) : (ptr[k++] = '-');
	while (n / i == 0)
		i /= 10;
	while (i)
	{
		ptr[k++] = n / i + '0';
		n = n % i;
		i /= 10;
	}
	return (ptr);
}
