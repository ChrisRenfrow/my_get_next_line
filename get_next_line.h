/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenfrow <crenfrow@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 12:58:24 by crenfrow          #+#    #+#             */
/*   Updated: 2016/12/02 05:59:56 by crenfrow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 8

/*
** Tour de t_file:
**
** buffer == The buffer from read()
** next == the ENTIRE next line if available, remains NULL when not in use
** file_desc == the file_descriptor, to be used in the case of multiple files
** found_eof == 1 if read() returned 0, 0 by default
** bytes_read == How many bytes read() has assigned to buffer
** bytes_parsed == how many bytes we've processed and given to **line
*/

typedef	struct	s_file
{
	char		buffer[BUFF_SIZE + 1];
	char		*next;
	int			file_desc;
	int			found_eof;
	int			bytes_read;
	int			bytes_parsed;
}				t_file;

int				get_next_line(const int fd, char **line);

#endif
