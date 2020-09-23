/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 19:07:06 by dfigg             #+#    #+#             */
/*   Updated: 2019/10/22 19:16:07 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_line(char **save, int fd)
{
	char	*line;
	char	*rest;
	size_t	i;

	i = 0;
	while (save[fd][i] != '\0')
	{
		if (save[fd][i] == '\n')
			break ;
		i++;
	}
	if (i != ft_strlen(save[fd]))
		rest = ft_strsub(save[fd], i + 1, ft_strlen(save[fd]) - i);
	else
		rest = ft_strnew(0);
	line = ft_strsub(save[fd], 0, i);
	line[i] = '\0';
	ft_strdel(&save[fd]);
	save[fd] = ft_strdup(rest);
	ft_strdel(&rest);
	return (line);
}

void	ft_savebuff(char **save, int fd, char *buff)
{
	char	*tmp;

	tmp = ft_strdup(save[fd]);
	ft_strdel(&save[fd]);
	save[fd] = ft_strjoin(tmp, buff);
	ft_strdel(&tmp);
}

int		get_next_line(const int fd, char **line)
{
	static char		*save[4048];
	char			buff[BUFF_SIZE + 1];
	int				rd;

	rd = 0;
	if (fd < 0 || !line || BUFF_SIZE < 0 || (read(fd, buff, 0) < 0))
		return (-1);
	if (!save[fd])
		save[fd] = ft_strnew(0);
	while ((!ft_strchr(save[fd], '\n')) && (rd = read(fd, buff, BUFF_SIZE)))
	{
		buff[rd] = '\0';
		ft_savebuff(save, fd, buff);
	}
	if (rd == 0 && ft_strlen(save[fd]) == 0)
	{
		ft_memset(*line, '\0', ft_strlen(*line));
		ft_strdel(&save[fd]);
		return (0);
	}
	*line = ft_get_line(save, fd);
	return (1);
}
