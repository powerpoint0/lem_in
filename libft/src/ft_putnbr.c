/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 09:46:16 by dfigg             #+#    #+#             */
/*   Updated: 2019/09/22 09:50:25 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned int	tmp;

	if (n < 0)
	{
		tmp = -n;
		ft_putchar('-');
	}
	else
		tmp = n;
	if (tmp >= 10)
	{
		ft_putnbr(tmp / 10);
		ft_putchar((tmp % 10) + '0');
	}
	else
	{
		if (n > 0)
			ft_putchar(('0' + n));
		else
			ft_putchar(('0' - n));
	}
}
