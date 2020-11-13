/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags_n_mods.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 09:33:44 by dfigg             #+#    #+#             */
/*   Updated: 2020/05/09 09:33:48 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		find_type(const char *format, t_prn *prn)
{
	int		i;
	int		size;
	char	type[17];

	set_str_values(type, "%diouxXeEfFgGscp\0", 17);
	size = 0;
	i = 0;
	while (format[size] != type[i])
	{
		if (format[size] == '\0')
			return (-1);
		if (type[i] == '\0')
		{
			i = 0;
			size++;
		}
		else
			i++;
	}
	prn->size = size;
	prn->type = format[prn->size];
	return (size);
}

int		set_flag(const char *format, t_prn *prn, int end)
{
	int		i;

	i = 0;
	while (i < end && (ft_strchr("-+ #0^", format[i]) != NULL))
	{
		if (format[i] == '-')
			prn->fl_minus = 1;
		if (format[i] == '+')
			prn->fl_plus = 1;
		if (format[i] == ' ')
			prn->fl_space = 1;
		if (format[i] == '#')
			prn->fl_sharp = 1;
		if (format[i] == '0')
			prn->fl_zero = 1;
		if (format[i] == '^')
			prn->fd = ft_get_signed_mod_llhh(prn);
		i++;
	}
	if (prn->fl_minus == 1 && prn->fl_zero == 1)
		prn->fl_zero = 0;
	return (i);
}

int		set_width(const char *format, int i, t_prn *prn)
{
	int		st;

	while ((format[i] == '*' || ft_isdigit(format[i])))
	{
		if (format[i] == '*')
		{
			if ((prn->width = ft_get_signed_mod_llhh(prn)) < 0)
			{
				prn->fl_minus = 1;
				prn->width *= -1;
				prn->fl_zero =(prn->fl_minus == 1 && prn->fl_zero == 1) ? 0 : prn->fl_zero;
			}
			i++;
		}
		st = i;
		if (format[i] == '0')
			return (-1);
		while (i < prn->size && ft_isdigit(format[i]))
			i++;
		if ((i == prn->size || ft_strchr("*.hlL", format[i])) && st != i)
			prn->width = strsub_to_int(format, st, i);
	}
	if (!(i == prn->size || ft_strchr(".hlL", format[i])))
		return (-1);
	return (i);
}

int		set_precision(const char *format, int i, t_prn *prn)
{
	int		st;

	if (format[i] == '.')
	{
		st = ++i;
		while (i < prn->size && ft_find_count("hlL", format[i]) == -1)
		{
			if (ft_isdigit(format[i]) == 0 && (format[i] != '*'))
				return (-1);
			i++;
		}
		if (format[st] == '*')
		{
			if ((prn->precision = ft_get_signed_mod_llhh(prn)) < 0)
				prn->precision = -1;
		}
		else
			prn->precision = strsub_to_int(format, st, i);
	}
	if (prn->precision > 0 && (ft_strchr("diouxX", format[prn->size]) != 0))
		prn->fl_zero = 0;
	return (i);
}

int		set_mod(const char *format, int i, t_prn *prn)
{
	if (prn->fd < 0)
	{
		prn->fd = 1;
		write(prn->fd, "error: fd < 0;\t", 15);
		return (-1);
	}
	if (ft_strchr("cspouxX", prn->type) != NULL)
		prn->fl_space = 0;
	prn->fl_space = (prn->fl_plus) ? 0 : prn->fl_space;
	if (format[i] == 'h' && i + 1 == prn->size)
		prn->mod_h = 1;
	else if (format[i] == 'h' && format[i + 1] == 'h' && i + 2 == prn->size)
		prn->mod_hh = 1;
	else if (format[i] == 'l' && i + 1 == prn->size)
		prn->mod_l = 1;
	else if (format[i] == 'l' && format[i + 1] == 'l' && i + 2 == prn->size)
		prn->mod_ll = 1;
	else if (format[i] == 'L' && i + 1 == prn->size)
		prn->mod_l_up = 1;
	else if (i != prn->size)
		return (-1);
	return (prn->size);
}
