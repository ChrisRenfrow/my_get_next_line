/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenfrow <crenfrow@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 16:45:09 by crenfrow          #+#    #+#             */
/*   Updated: 2016/12/05 01:02:44 by crenfrow         ###   ########.fr       */
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
	file->found_eof		= 0;
	file->bytes_read	= 0;
	file->bytes_parsed	= 0;
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
// Close but no cigar, need to figure out reliable way to advance the working
// buffer to the next section. Make use of bytes_parsed?
int get_line(t_file **file)
{
	int llen;
	int ret;
	char *buffer;
	t_file *fptr;

	llen = 0;
	fptr = *file;
	ft_strclr(fptr->nline);
	buffer = fptr->buffer;
	while (fptr->buffer[llen] != '\n')
	{
		if (fptr->next[0])
		{
			fptr->nline = ft_strjoin(fptr->nline, fptr->next);
			ft_strclr(fptr->next);
		}
		if (fptr->bytes_parsed >= fptr->bytes_read)
		{
			ret = read(fptr->file_desc, buffer, BUFF_SIZE);
			if (ret <= 0)
				return (ret);
		}
		llen = ft_strlchr(buffer, '\n');
		if (llen == 0)
			return (0);
		if (llen < BUFF_SIZE)
		{
			fptr->nline = ft_strjoin(fptr->nline, ft_strsub(buffer, 0, llen));
			fptr->next = ft_strsub(buffer, llen + 1, \
				ft_strlchr(buffer + (llen + 1), '\n'));
		}
		else
			fptr->nline = ft_strjoin(fptr->nline, buffer);
		fptr->bytes_parsed += llen;
	}
	return (1);
}

int get_next_line(const int fd, char **line)
{
	static t_file	*file;
	int 			ret;

	if (fd < 3 || !line)
		return (-1);
	if (!file)
		file = init_file(fd);
	ret = get_line(&file);
	if (ret <= 0)
		return (ret);
	*line = ft_strdup(file->nline);
	return (1);
}
