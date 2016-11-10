/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenfrow <crenfrow@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 12:50:29 by crenfrow          #+#    #+#             */
/*   Updated: 2016/11/10 12:11:42 by crenfrow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int		line_length(char *buffer, char c)
{
	int length;

	length = 0;
	while (buffer[length] != c && buffer[length])
		length++;
	return (length);
}

int		get_line(char *buffer, char **line)
{
	int len;

	len = line_length(buffer, '\n');
	if (len == 0)
		return (0);
	*line = ft_strjoin(*line, ft_strsub(buffer, 0, len));
	if (buffer[len] != '\n')
		return (1);
	else
		return (0);
}

int		get_next_line(const int fd, char **line)
{
	static t_file	*file;
	int				fs;
	int				len;

	if (fd < 0 || !line)
		return (-1);
	fs = 1;
	if (!file)
	{
		file = (t_file *)ft_memalloc(sizeof(t_file));
		file->file_desc = fd;
		file->status = 1;
	}
	while (fs)
	{
		len = line_length(file->buffer, '\n');
		if (file->buffer[len] == '\n')
		{
			*line = ft_strdup(file->buffer +
				line_length(file->buffer, '\n') + 1);
		}
		if (file->status == 1)
		{
			fs = read(fd, file->buffer, BUFF_SIZE);
			if (fs < BUFF_SIZE)
			{
				file->status = 0;
				file->next = file->buffer;
			}
		}
		if (file->status == 1)
			fs = get_line(file->buffer, line);
		else
		{
			fs = get_line(file->next, line);
			file->next = ft_strchr(file->next, '\n') + 1;
			// if ()
			// 	return (0);
		}
		// if (!file->buffer[ft_strlen(file->buffer)])
		// 	return (0);
	}
	return (1);
}
