/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 00:59:17 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/09/18 01:47:53 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char *ptr;

	if (!(ptr = (char*)malloc(sizeof(*ptr) * (size))))
		return (NULL);
	else
		ft_bzero(ptr, size);
	return (ptr);
}
