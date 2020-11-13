/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 06:59:50 by dfigg             #+#    #+#             */
/*   Updated: 2020/05/07 06:59:57 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		cut_str(char *str, t_prn *prn)
{
	int	count;

	count = ft_strlen(str) - 1;
	while (str[count] == '0')
	{
		str[count] = '\0';
		count--;
	}
	if (str[count] == '.' && prn->fl_sharp == 0)
		str[count] = '\0';
}

int			ft_isnan(long double nbr)
{
	t_inf_nan	tnan;

	tnan.d = (double)nbr;
	if (tnan.l == 0x7FF8000000000000 || tnan.l == 0xFFF8000000000000)
		return (1);
	return (0);
}

int			ft_isinf(long double nbr)
{
	t_inf_nan	tnan;

	tnan.d = (double)nbr;
	if (tnan.l == 0x7FF0000000000000)
		return (1);
	if (tnan.l == 0xFFF0000000000000)
		return (-1);
	return (0);
}

int			nan_inf(long double nbr, t_prn *prn, char *str)
{
	if (ft_isnan(nbr))
	{
		if (ft_islower(prn->type))
			ft_strcpy(str, "nan");
		else
			ft_strcpy(str, "NAN");
		prn->fl_zero = 0;
		prn->fl_plus = 0;
		prn->sign = 0;
		return (1);
	}
	if (ft_isinf(nbr) != 0)
	{
		str[0] = (ft_isinf(nbr) < 0) ? '-' : '+';
		if (ft_islower(prn->type))
			ft_strcpy(&str[1], "inf");
		else
			ft_strcpy(&str[1], "INF");
		prn->fl_zero = 0;
		prn->sign = 0;
		return (1);
	}
	return (0);
}

void		move_under_one(char *str, int degree)
{
	int	size;

	degree = -degree;
	size = ft_strlen(str);
	while (size >= 0)
	{
		str[size + degree] = str[size];
		size--;
	}
	while (--degree >= 0)
		str[degree] = '0';
}
