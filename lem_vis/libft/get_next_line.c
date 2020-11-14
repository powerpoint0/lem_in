/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <cjoaquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 05:08:54 by cjoaquin          #+#    #+#             */
/*   Updated: 2019/10/18 18:04:23 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_freeall(char *tmp, char *c)
{
	ft_strdel(&tmp);
	free(c);
	return (-1);
}

static char	*ft_poiskn(ssize_t *b, int fd, char *c, char *buffer)
{
	char		*tmp;

	*b = 0;
	while (!ft_strchr(c, '\n') && (*b = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[*b] = '\0';
		tmp = c;
		if (!(c = ft_strjoin(c, buffer)))
			ft_freeall(tmp, c);
		ft_strdel(&tmp);
	}
	return (c);
}

int			get_next_line(const int fd, char **line)
{
	static char	*c[11000];
	char		buffer[BUFF_SIZE + 1];
	char		*tmp;
	ssize_t		b;
	int			endl;

	if (fd < 0 || fd > 11000 || (!c[fd] && !(c[fd] = ft_strnew(1))) || !line)
		return (-1);
	c[fd] = ft_poiskn(&b, fd, c[fd], buffer);
	if (b == -1 || *(tmp = c[fd]) == 0)
		return (b == -1 ? -1 : 0);
	if ((endl = (ft_strchr(c[fd], '\n') != 0)))
	{
		if (!(*line = ft_strsub(c[fd], 0, ft_strchr(c[fd], '\n') - c[fd])))
			ft_freeall(tmp, c[fd]);
	}
	else if (!(*line = ft_strdup(c[fd])))
		ft_freeall(tmp, c[fd]);
	if (!(c[fd] = ft_strsub(c[fd], (unsigned int)(ft_strlen(*line) + endl),
					(size_t)(ft_strlen(c[fd]) - (ft_strlen(*line) + endl)))))
		ft_freeall(tmp, c[fd]);
	ft_strdel(&tmp);
	return (c[fd] || ft_strlen(*line));
}
