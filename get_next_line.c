/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenfrow <crenfrow@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 12:50:29 by crenfrow          #+#    #+#             */
/*   Updated: 2016/12/02 06:00:19 by crenfrow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// Function count: 3 of 5

char	*ft_realloc(char *orig, int new)
{
	char *fresh;
	fresh = ft_strnew(new);
	fresh = ft_strcpy(fresh, orig);
	free(orig);
	return (fresh);
}

t_file	*init_file(int fd)
{
	t_file *file;

	file				= (t_file *)ft_memalloc(sizeof(t_file));
	file->next 			= 0;
	file->file_desc		= fd;
	file->found_eof		= 0;
	file->bytes_read	= 0;
	file->bytes_parsed	= 0;
	return (file);
}

int		line_len(char *buff)
{
	int len;

	len = 0;
	while (buff[len] != '0' && buff[len] != '\n')
		len++;
	if (buff[len] == '\n')	// If the end character is a '\n'
		return(len - 1);	// Return len minus 1
	return (len);			// Otherwise return len
}

// int		get_line(char **line, t_file **file)
// {
// 	if ()
// 	return (1);
// }

int		get_next_line(const int fd, char **line)
{
	static	t_file *file;		// Static variable to save across instances
	int 	rs;					// Read Status: Return value from read()
	int		ls;					// Line Status: Return value from get_line()

	rs = 0;
	ls = 1;
	if (!file)					// If file has not been initialized
		file = init_file(fd);	// Initialize new t_file
	if (fd < 3 || !line)		// Input check
		return (-1);			// Bad input: return -1
	while (ls)					// While line is unfinished
	{							// Continue reading
		if (!file->found_eof)	// If EOF has been found, skip to get_line
		{
			if (!(rs = read(fd, file->buffer, BUFF_SIZE)))
				return (-1);				// Returns -1 if read err
			if (rs == 0) 					// read() has found EOF
				file->found_eof = 1;
			file->buffer[rs] = 0; 			// Null terminating
			file->bytes_read += rs;			// Update bytes read
		}
		ls = get_line(line, &file);
		if (file->bytes_parsed >= file->bytes_read)
			return (0);						// End condition
	}
	return (1);
}
