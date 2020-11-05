/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 01:40:59 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/18 01:49:13 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *ptr;

	if (!(ptr = (char*)malloc(sizeof(*ptr) * (size + 1))))
		return (NULL);
	else
		ft_bzero(ptr, size + 1);
	return (ptr);
}
