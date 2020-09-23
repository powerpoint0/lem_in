/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 16:47:48 by dfigg             #+#    #+#             */
/*   Updated: 2019/09/20 18:36:17 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_firsts(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\n' || str[i] == '\t'
			|| str[i] == '\v' || str[i] == '\r'
			|| str[i] == '\f' || str[i] == ' ')
		i++;
	return (i);
}

int			ft_atoi(const char *str)
{
	int			i;
	int			sig;
	int long	rez;

	i = 0;
	sig = 1;
	rez = 0;
	i = ft_firsts(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sig = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rez = rez * 10 + (str[i] - '0');
		i++;
	}
	if ((sig * rez) > 0 && sig < 0)
		return (0);
	if ((sig * rez) < 0 && sig > 0)
		return (-1);
	return (sig * rez);
}
