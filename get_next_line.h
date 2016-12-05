/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenfrow <crenfrow@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 12:58:24 by crenfrow          #+#    #+#             */
/*   Updated: 2016/12/05 00:59:38 by crenfrow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 8

/*
** Tour de t_file:
**
**
*/

typedef	struct	s_file
{
	char		buffer[BUFF_SIZE + 1];
	char		*nline;
	char		*next;
	int			file_desc;
	int			found_eof;
	int			bytes_read;
	int			bytes_parsed;
}				t_file;

int				get_next_line(const int fd, char **line);

#endif
