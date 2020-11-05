/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 23:44:52 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/20 00:19:15 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_params(int argc, char **argv)
{
	int i;
	int j;

	i = 1;
	j = 0;
	if (argc > 1)
	{
		while (i < argc)
		{
			while (argv[i][j])
			{
				ft_putchar(argv[i][j]);
				j++;
			}
			ft_putchar('\n');
			i++;
			j = 0;
		}
	}
}
