/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenfrow <crenfrow@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 12:50:29 by crenfrow          #+#    #+#             */
/*   Updated: 2016/11/19 08:17:26 by crenfrow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// OMFG REMOVE THIS BEFORE SUBMITTING
#include <stdio.h>
/////////////////////////////////////

int line_len(char *buff)
{
	int i;

	i = 0;
	if (buff)
	{
		while(buff[i] != '\n' && buff[i])
			i++;
	}
	return (i);
}

int		get_line(t_file **file, char *buffer, char **line)
{
	int len;
	int nxt_len;

	len = line_len(buffer);
	nxt_len = 0;
	if ((*file)->next)
	{
		*line = ft_strdup(ft_strjoin(*line, (*file)->next));
		ft_strclr((*file)->next);
	}
	if (len < BUFF_SIZE && buffer[len + 1])
	{
		nxt_len = line_len(ft_strchr(buffer, '\n') + 1);
		(*file)->next = ft_strdup(ft_strsub(ft_strchr(&buffer[len + 2], '\n'), 0, nxt_len));
	}
	*line = ft_strdup(ft_strjoin(*line, ft_strsub(buffer, 0, len)));
	if (len < BUFF_SIZE && !buffer[len])
		return (0);
	else
		return (1);
}

int		get_next_line(const int fd, char **line)
{
	static t_file	*file;
	int			 	fs; // File-status
	int				ls; // Line-status

	if (fd < 0 || !line)
		return (-1);
	fs = 1;
	ls = 1;
	if (!file)
	{
		file = (t_file *)ft_memalloc(sizeof(t_file));
		file->file_desc = fd;
		file->status = 1;
	}
	if (file->line_sz == 0)
		ft_strclr(*line);
	while (ls)
	{
		if (file->status == 1)
		{
			fs = read(fd, file->buffer, BUFF_SIZE);
			if (fs < BUFF_SIZE)
				file->status = 0;
			file->buffer[fs] = 0;
			ls = get_line(&file, file->buffer, line);
		}
		else
			ls = get_line(&file, &(file)->buffer[file->file_read + 1], line);
		if (!file->buffer[file->file_read] && !file->status)
			return (0);
	}
	return (1);
}
