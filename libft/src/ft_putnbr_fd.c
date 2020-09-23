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

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	tmp;

	if (n < 0)
	{
		tmp = -n;
		ft_putchar_fd('-', fd);
	}
	else
		tmp = n;
	if (tmp >= 10)
	{
		ft_putnbr_fd(tmp / 10, fd);
		ft_putchar_fd(((tmp % 10) + '0'), fd);
	}
	else
	{
		if (n > 0)
			ft_putchar_fd(('0' + n), fd);
		else
			ft_putchar_fd(('0' - n), fd);
	}
}
