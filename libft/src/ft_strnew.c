/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 12:37:56 by dfigg             #+#    #+#             */
/*   Updated: 2019/09/21 14:04:48 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*tmp;

	if ((size + 1) < size)
		return (NULL);
	if (!(tmp = (char*)ft_memalloc(size + 1)))
		return (NULL);
	return (tmp);
}
