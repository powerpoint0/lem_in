/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 09:42:08 by dfigg             #+#    #+#             */
/*   Updated: 2020/05/15 09:42:14 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_islower(int ch)
{
	if (ch >= 'a' && ch <= 'z')
		return (1);
	if (ch >= 'A' && ch <= 'Z')
		return (0);
	else
		return (-1);
}

void	set_str_values(char *str, char *values, int size)
{
	bzero(str, size);
	while (--size >= 0)
	{
		str[size] = values[size];
	}
}

int		strsub_to_int(const char *str, int st, int end)
{
	int		rez;

	rez = 0;
	while (st < end)
		rez = rez * 10 + (str[st++] - '0');
	return (rez);
}

int		ft_round9(char *str, int count, int degree)
{
	str[count + 1] = '\0';
	while (count >= 0)
	{
		if (count == 0 && str[count] == '9')
		{
			str[count] = '1';
			degree++;
			str[ft_strlen(str)] = '0';
			str[ft_strlen(str) + 1] = '\0';
		}
		else
		{
			if (count != 0 && str[count] == '9')
				str[count] = '0';
			else
			{
				str[count] = str[count] + 1;
				count = 0;
			}
		}
		count--;
	}
	return (degree);
}

int		ft_find_count(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if ((char)c == '\0')
		return (i);
	return (-1);
}
