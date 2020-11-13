/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ouxX_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 09:32:40 by dfigg             #+#    #+#             */
/*   Updated: 2020/05/09 09:32:47 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t	ft_get_unsigned_mod_llhh(t_prn *prn)
{
	uintmax_t	nbr;

	nbr = va_arg(prn->ap, uintmax_t);
	if (prn->mod_hh)
		nbr = (unsigned char)nbr;
	else if (prn->mod_h)
		nbr = (unsigned short int)nbr;
	else if (prn->mod_l)
		nbr = (unsigned long int)nbr;
	else if (prn->mod_ll)
		nbr = (unsigned long long int)nbr;
	//else if (arg->length == j)
		//nbr = (uintmax_t)nbr;
	//else if (arg->length == z)
		//nbr = (size_t)nbr;
	else
		nbr = (unsigned int)nbr;
	return (nbr);
}

void		ft_itoa16(uintmax_t num, char *rez, int base, char *basee)
{
	int			size;
	uintmax_t	tmp;

	size = 1;
	tmp = num;
	if (num == 0)
	{
		*rez = '0';
		return ;
	}
	while (tmp /= base)
		size++;
	while (size--)
	{
		rez[size] = basee[num % base];
		num /= base;
	}
}

int			print_p(t_prn *prn)
{
	size_t	num;
	char	str[27];
	int		len;
	int		size;

	ft_bzero(str, 27);
	num = va_arg(prn->ap, size_t);
	ft_itoa16(num, str, 16, "0123456789abcdef");
	if (!num && prn->precision == 0)
		ft_bzero(str, 27);
	len = ft_strlen(str);
	prn->precision = (len < prn->precision) ? prn->precision : len;
	if (!num && prn->fl_zero && prn->width > prn->precision)
		prn->precision = prn->width - 2;
	len = (len < prn->precision) ? prn->precision + 2 : len + 2;
	size = (len > prn->width) ? len : prn->width;
	ft_print_number(len, size, str, prn);
	prn->size_symb += size;
	return (size);
}

int			print_oux(t_prn *prn)
{
	int			len;
	int			size;
	char		str[27];
	uintmax_t	num;

	ft_bzero(str, 27);
	prn->sign = 0;
	num = ft_get_unsigned_mod_llhh(prn);
	if (prn->type == 'o')
		ft_itoa16(num, str, 8, "01234567");
	else if (prn->type == 'u')
		ft_itoa16(num, str, 10, "0123456789");
	else if (prn->type == 'x')
		ft_itoa16(num, str, 16, "0123456789abcdef");
	else if (prn->type == 'X')
		ft_itoa16(num, str, 16, "0123456789ABCDEF");
	len = ft_count_len(ft_strlen(str), str, prn);
	size = (prn->width > len) ? prn->width : len;
	ft_print_number(len, size, str, prn);
	prn->size_symb += size;
	return (size);
}
