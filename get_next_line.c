/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenfrow <crenfrow@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 16:45:09 by crenfrow          #+#    #+#             */
/*   Updated: 2016/12/06 05:20:02 by crenfrow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	 == Mk.3 :rolling_eyes: ==
**	In this version my focus is to only call read when I need to instead of
**	trying to manage both the buffer and line simultaneously.
*/

#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

/*
**	V libft addition candidates V
*/

/*
**	Finds the length of the string up to NULL or the specified char
*/

int ft_strlchr(char *str, int c)
{
	int l;

	l = 0;
	while (str[l] != 0 && str[l] != c)
		l++;
	return (l);
}

/*
**	V get_next_line functions V
*/

t_file	*init_file(int fd)
{
	t_file *file;

	file				= (t_file *)ft_memalloc(sizeof(t_file));
	file->next 			= ft_strnew(1);
	file->nline			= ft_strnew(1);
	file->file_desc		= fd;
	return (file);
}

int read_buffer(t_file **file)
{
	int ret;
	t_file *fptr;

	ret = 0;
	fptr = *file;
	ret = read(fptr->file_desc, fptr->buffer, BUFF_SIZE);
	fptr->buffer[ret] = 0;
	fptr->bytes_read += ret;
	if (ret < BUFF_SIZE)
		fptr->found_eof++;
	if (ret < 0)
		return (-1);
	return (ret);
}

int get_line(t_file **file)
{
	int llen;
	int ret;
	t_file *fptr;

	llen = 0;
	fptr = *file;
	if (!fptr->next[0])
		ret = read_buffer(file);
	ft_strclr(fptr->nline);
	while ((fptr->next[0] || fptr->buffer[0]) && !fptr->found_eof)
	{
		if (fptr->next[0])
		{
			llen = ft_strlchr(fptr->next, '\n');
			fptr->nline = ft_strjoin(fptr->nline, \
				ft_strsub(fptr->next, 0, llen));
			fptr->bytes_parsed += llen + 1;
			fptr->next = fptr->next + (llen + 1);
			if (fptr->next[llen] == '\n')
				return (1);
			else
				ret = read_buffer(file);
		}
		llen = ft_strlchr(fptr->buffer, '\n');
		if (llen < BUFF_SIZE)
		{
			fptr->nline = ft_strjoin(fptr->nline, \
				ft_strsub(fptr->buffer, 0, llen));
			fptr->bytes_parsed += llen;
			fptr->next = ft_strdup(fptr->buffer + (llen + 1));
			return (1);
		}
		else
		{
			fptr->nline = ft_strjoin(fptr->nline, fptr->buffer);
			fptr->bytes_parsed += BUFF_SIZE;
			ret = read_buffer(file);
		}
	}
	// if (fptr->bytes_parsed <= fptr->bytes_read)
	// 	return (ret);
	return (0);
}

int get_next_line(const int fd, char **line)
{
	static t_file	*file;
	int 			ret;

	if (fd < 0 || !line)
		return (-1);
	if (!file)
		file = init_file(fd);
	ret = get_line(&file);
	if (ret <= 0)
		return (ret);
	*line = ft_strdup(file->nline);
	return (1);
}
