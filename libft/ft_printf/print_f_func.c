/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 06:58:53 by dfigg             #+#    #+#             */
/*   Updated: 2020/05/07 06:59:03 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		get_degree(long double *nbr)
{
	int			degree;
	double		s;

	degree = 0;
	s = (*nbr) - 0.1 * (*nbr);
	if (s < 1e-16)
		return (0);
	if ((*nbr) < 1.0f)
	{
		while ((*nbr) < 1.0)
		{
			*nbr *= 10.0;
			degree--;
		}
	}
	else
		while ((*nbr) >= 10.0)
		{
			degree++;
			*nbr /= 10.0;
		}
	return (degree);
}

void	add_exp(char *str, int degree, t_prn *prn)
{
	int	count;
	int	tmp;

	count = ft_strlen(str);
	str[count++] = (ft_islower(prn->type) == 1) ? 'e' : 'E';
	str[count++] = (degree < 0) ? '-' : '+';
	degree = (degree < 0) ? -degree : degree;
	if (degree < 10)
	{
		str[count++] = '0';
		str[count++] = degree + '0';
		str[count] = '\0';
	}
	else
	{
		tmp = degree;
		while (tmp /= 10)
			count++;
		str[count + 1] = '\0';
		while (degree > 0)
		{
			str[count--] = (degree % 10) + '0';
			degree /= 10;
		}
	}
}

void	print_flag_str(t_prn *prn, int len)
{
	int		i;
	char	sign;
	char	ch;

	sign = (prn->sign == 1) ? '-' : '+';
	if ((prn->fl_plus == 1 || prn->sign == 1) && prn->fl_minus == 0)
	{
		if (prn->width > len)
			prn->width -= 1;
		if (prn->fl_zero == 1)
			prn->size_symb += write(1, &sign, 1);
	}
	i = 0;
	ch = (prn->fl_zero == 1) ? '0' : ' ';
	while (i++ < (prn->width - len))
		prn->size_symb += write(1, &ch, 1);
	if ((prn->fl_plus == 1 || prn->sign == 1) && prn->fl_minus == 0
		&& prn->fl_zero == 0)
		prn->size_symb += write(1, &sign, 1);
}

int		print_format2(t_prn *prn, char *str)
{
	int len;

	len = ft_strlen(str);
	if (prn->width < len)
		prn->width = (prn->sign == 0) ? len : (len + 1);


	return (prn->width);
}


int		print_format(t_prn *prn, char *str)
{
	int	len;

	len = ft_strlen(str);
	if (prn->width < len)
		prn->width = (prn->sign == 0) ? len : (len + 1);
	if (prn->fl_space == 1 && prn->fl_plus != 1 && prn->sign != 1)
	{
		prn->size_symb += write(1, " ", 1);
		prn->width--;
	}
	if (prn->fl_minus == 1)
	{
		if (prn->fl_plus == 1 || prn->sign == 1)
		{
			(prn->sign == 1) ? write(1, "-", 1) : write(1, "+", 1);
			prn->size_symb++;
			prn->width--;
		}
		prn->size_symb += write(1, str, ft_strlen(str));
		print_flag_str(prn, len);
	}
	else
	{
		print_flag_str(prn, len);
		prn->size_symb += write(1, str, ft_strlen(str));
	}
	return (prn->width);
}

void	add_point(char *str, t_prn *prn, int degree)
{
	int	len;
	int	count;

	if (prn->type == 'g' || prn->type == 'G')
		count = (degree < 0 || ((degree - prn->precision) >= 0
		&& degree > 0)) ? 1 : degree + 1;
	else
		count = (prn->type == 'e' || prn->type == 'E' || degree <= 0) ?
			1 : degree + 1;
	if (prn->precision == 0 && prn->fl_sharp == 0)
		str[count] = '\0';
	else
	{
		len = ft_strlen(str) + 1;
		str[len + 1] = '\0';
		while (len > (count))
		{
			str[len] = str[len - 1];
			len--;
		}
		str[count] = '.';
	}
}
