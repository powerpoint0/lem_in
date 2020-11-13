/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 09:32:20 by dfigg             #+#    #+#             */
/*   Updated: 2020/05/09 09:32:28 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_type_csp(int size, int len, t_prn *prn, char *str)
{
	int		i;
	char	c;

	i = 0;
	c = (prn->fl_zero) ? '0' : ' ';
	while (i < size)
	{
		if (prn->fl_minus == 0)
			(i < (size - len)) ? (write(prn->fd, &c, 1)) :
			(write(prn->fd, &str[i - (size - len)], 1));
		if (prn->fl_minus == 1)
			(i < len) ? write(prn->fd, &str[i], 1) : write(prn->fd, &c, 1);
		i++;
	}
}

int		print_c(t_prn *prn)
{
	char	str[1];
	int		size;
	int		len;

	size = (prn->width) ? (prn->width) : 1;
	len = 1;
	if (prn->type != '%')
		str[0] = (char)va_arg(prn->ap, int);
	else
		str[0] = '%';
	ft_print_type_csp(size, len, prn, str);
	prn->size_symb += size;
	return (prn->size_symb);
}

int		print_s(t_prn *prn)
{
	int		len;
	char	*str;
	int		size;
	char	null[7];

	set_str_values(null, "(null)", 7);
	if (!(str = va_arg(prn->ap, char*)))
		str = null;
	if (prn->precision > (int)(ft_strlen(str)) || prn->precision == -1)
		prn->precision = ft_strlen(str);
	len = prn->precision;
	size = ft_strlen(str);
	if (prn->width)
		size = (prn->width > prn->precision) ? prn->width : prn->precision;
	else if (prn->precision >= 0)
		size = prn->precision;
	ft_print_type_csp(size, len, prn, str);
	prn->size_symb += size;
	return (prn->size_symb);
}

int		print_txt(const char *format, int size, t_prn *prn)
{
	int	i;

	i = 0;
	while (i < size && format[i] != '\0')
	{
		if (format[i] == '^')
		{
			prn->fd = ft_get_signed_mod_llhh(prn);
			if (prn->fd < 0)
			{
				write(1, "\tundefined behavior: fd < 0;\t", 29);
				return (-1);
			}
		}
		else
		{
			write(prn->fd, &format[i], 1);
			prn->size_symb++;
		}
		i++;
	}
	return (0);
}
