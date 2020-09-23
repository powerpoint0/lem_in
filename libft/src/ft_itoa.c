/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 12:31:00 by dfigg             #+#    #+#             */
/*   Updated: 2019/09/21 12:49:52 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sig(int n)
{
	int		minus;

	minus = 0;
	if (n < 0)
		minus = 1;
	else
		minus = 0;
	return (minus);
}

char		*ft_itoa(int n)
{
	int			size;
	int			minus;
	long int	tmp;
	char		*rez;

	minus = ft_sig(n);
	tmp = n;
	size = 1;
	while (n /= 10)
		size++;
	rez = ft_strnew(size + minus);
	if (rez == NULL)
		return (NULL);
	if (minus)
		rez[0] = '-';
	while (size--)
	{
		if (minus == 1)
			rez[size + minus] = -(tmp % 10) + '0';
		else
			rez[size + minus] = (tmp % 10) + '0';
		tmp /= 10;
	}
	return (rez);
}
