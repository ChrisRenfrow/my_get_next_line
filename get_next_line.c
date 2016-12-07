/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenfrow <crenfrow@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 21:31:49 by crenfrow          #+#    #+#             */
/*   Updated: 2016/12/07 05:37:50 by crenfrow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	handle_line(char *buff, char **line)
{
	int		llen;

	llen = ft_strlchr(buff, '\n');
	*line = ft_realloc(*line, llen + ft_strlen(*line));
	*line = ft_strjoin(*line, ft_strsub(buff, 0, llen));
	return (llen);
}

int			get_next_line(const int fd, char **line)
{
	static char		*buff;
	int				llen;
	int				ret;

	if (fd < 0 || !line)
		return (-1);
	if (!buff)
		buff = ft_strnew(BUFF_SIZE);
	ret = 1;
	*line = ft_strnew(1);
	while (ret > 0)
	{
		if (!buff[0])
		{
			if ((ret = read(fd, buff, BUFF_SIZE)) < 0)
				return (ret);
			buff[ret] = 0;
		}
		llen = handle_line(buff, line);
		if (llen < BUFF_SIZE && buff[llen] == '\n')
		{
			buff = buff + llen + 1;
			return (1);
		}
		ft_strclr(buff);
	}
	return (0);
}
