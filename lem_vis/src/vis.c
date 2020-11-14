/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 15:22:42 by dfigg             #+#    #+#             */
/*   Updated: 2020/11/14 15:22:44 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vis.h>

void	free_str(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			ft_strdel(&str[i]);
			i++;
		}
		free(str);
	}
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

int		put_err(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

int		ft_atoi_check(const char *str)
{
	int			i;
	int			sig;
	int long	rez;

	i = 0;
	sig = 1;
	rez = 0;
	if (str[i] == '-')
		sig = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		rez = rez * 10 + (str[i] - '0');
		i++;
	}
	if (i == 0 || rez > INT32_MAX || ft_strlen(str) > 14)
		put_err("ERROR.Not valid int");
	return (sig * (int)rez);
}

int		main(void)
{
	t_vmap *map;

	map = read_map();
	ft_drawing(map);
	return (0);
}
