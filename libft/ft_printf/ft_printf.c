/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 10:00:09 by dfigg             #+#    #+#             */
/*   Updated: 2020/05/09 10:00:14 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	clear_format(t_prn *prn)
{
	prn->fl_minus = 0;
	prn->fl_plus = 0;
	prn->fl_space = 0;
	prn->fl_sharp = 0;
	prn->fl_zero = 0;
	prn->width = 0;
	prn->precision = -1;
	prn->mod_h = 0;
	prn->mod_hh = 0;
	prn->mod_l = 0;
	prn->mod_ll = 0;
	prn->mod_l_up = 0;
	prn->size = 0;
	prn->sign = 0;
	prn->type = '0';
}

int		set_param(const char *format, t_prn *prn)
{
	int	i;

	i = 0;
	if (((find_type(format, prn)) == -1) ||
		(i = set_flag(format, prn, prn->size)) == -1 ||
		(i = set_width(format, i, prn)) == -1 ||
		((i = set_precision(format, i, prn)) == -1) ||
		(set_mod(format, i, prn)) == -1)
	{
		write(prn->fd, "undefined_behavior: wrong format", 32);
		return (-1);
	}
	return (0);
}

int		parsing_type(const char *format, t_prn *prn)
{
	if ((set_param(format, prn)) == -1)
		return (-1);
	if (format[prn->size] == 'd' || format[prn->size] == 'i')
		print_di(prn);
	if (format[prn->size] == 's')
		print_s(prn);
	if (format[prn->size] == 'c' || format[prn->size] == '%')
		print_c(prn);
	if (format[prn->size] == 'p')
		print_p(prn);
	if (format[prn->size] == 'o' || format[prn->size] == 'u' ||
		format[prn->size] == 'x' || format[prn->size] == 'X')
		print_oux(prn);
	if (format[prn->size] == 'f' || format[prn->size] == 'F' ||
		format[prn->size] == 'g' || format[prn->size] == 'G' ||
		format[prn->size] == 'e' || format[prn->size] == 'E')
		print_efg(prn);
	return (0);
}

int		ft_algoritm(const char *format, t_prn *prn)
{
	int		fcount;

	while ((fcount = ft_find_count(format, '%')) >= 0)
	{
		if (format[fcount + 1] == '%')
		{
			print_txt(format, fcount + 1, prn);
			format += fcount + 2;
		}
		else
		{
			print_txt(format, fcount, prn);
			format += fcount + 1;
			if ((parsing_type(format, prn)) == -1)
				return (-1);
			format += prn->size + 1;
			clear_format(prn);
		}
	}
	if (*format != '\0')
		print_txt(format, ft_find_count(format, '\0'), prn);
	return (0);
}

int		ft_printf(const char *format, ...)
{
	t_prn	prn;

	prn.fd = 1;
	prn.size_symb = 0;
	clear_format(&prn);
	va_start(prn.ap, format);
	ft_algoritm(format, &prn);
	va_end(prn.ap);
	return (prn.size_symb);
}
