/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_efg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 06:59:17 by dfigg             #+#    #+#             */
/*   Updated: 2020/05/07 06:59:23 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

long double	get_nbr(t_prn *prn)
{
	long double		nbr;

	if (prn->mod_l_up == 1)
		nbr = va_arg(prn->ap, long double);
	else
		nbr = (long double)va_arg(prn->ap, double);
	if (nbr < 0.0f)
	{
		nbr = -nbr;
		prn->sign = 1;
	}
	else
		prn->sign = 0;
	return (nbr);
}

void		write_to_string(long double nbr, char *str, t_prn *prn, int degree)
{
	int	i;
	int size_d;

	i = 0;
	size_d = (degree > 0) ? (degree + 1) : 1;
	while (i < (prn->precision + size_d + 1) && i < 315)
	{
		str[i] = (unsigned int)nbr + '0';
		nbr -= (unsigned int)nbr;
		nbr *= 10.0;
		i++;
	}
}

int			calc_size(int degree, t_prn *prn)
{
	int	size;

	if (prn->type == 'g' || prn->type == 'G')
	{
		size = (degree < 0 && degree > -5) ?
			((-degree) + prn->precision) : prn->precision;
	}
	else
	{
		size = (prn->type == 'e' || prn->type == 'E' || degree <= 0) ?
				(1 + prn->precision) : (1 + degree + prn->precision);
	}
	return (size);
}

int			correct_str(char *str, t_prn *prn, int degree)
{
	int	size;

	if (((prn->type == 'f' || prn->type == 'F') && degree < 0) ||
			((prn->type == 'g' || prn->type == 'G') &&
			(degree > -5 && degree < 0)))
		move_under_one(str, degree);
	size = calc_size(degree, prn);
	if (str[size] >= '5' && str[size] <= '9')
	{
		if (str[size - 1] == '9')
		{
			degree = ft_round9(str, size - 1, degree);
			size = calc_size(degree, prn);
		}
		else
			str[size - 1] = str[size - 1] + 1;
	}
	str[size] = '\0';
	add_point(str, prn, degree);
	return (degree);
}

int			print_efg(t_prn *prn)
{
	long double	nbr;
	char		str[315];
	int			degree;

	ft_bzero(str, 315);
	nbr = get_nbr(prn);
	if (!nan_inf(nbr, prn, str))
	{
		degree = get_degree(&nbr);
		if (prn->precision == -1)
			prn->precision = 6;
		write_to_string(nbr, str, prn, degree);
		degree = correct_str(str, prn, degree);
		if (prn->type == 'e' || prn->type == 'E')
			add_exp(str, degree, prn);
		if (prn->type == 'g' || prn->type == 'G')
		{
			cut_str(str, prn);
			if (degree < -4 || ((degree - prn->precision) >= 0 &&
				degree > 0))
				add_exp(str, degree, prn);
		}
	}
	print_format(prn, str);
	return (0);
}
