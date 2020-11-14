/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 16:34:22 by dfigg             #+#    #+#             */
/*   Updated: 2020/11/14 16:34:26 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

int		ft_find_err(char *str)
{
	char	*err;
	int		i;
	int		j;

	i = 0;
	j = 0;
	err = "ERROR";
	while (str[i] != '\0' && str[i] != err[0])
		i++;
	while (str[i] == err[j] && str[i] != '\0')
	{
		i++;
		j++;
	}
	err = NULL;
	if (j == 5)
		return (1);
	else
		return (0);
}
