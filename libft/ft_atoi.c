/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 04:52:26 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/20 23:28:55 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int			sign;
	long long	check;
	long long	resalt;

	check = 0;
	resalt = 0;
	sign = 1;
	while (*str == '\n' || *str == '\t' || *str == '\r'
		|| *str == '\v' || *str == '\f' || *str == ' ')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		check = resalt;
		resalt = resalt * 10 + (*str - '0');
		if (check != resalt / 10)
			return (sign == 1 ? -1 : 0);
		str++;
	}
	return ((int)resalt * sign);
}
