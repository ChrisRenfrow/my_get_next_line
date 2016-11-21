/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenfrow <crenfrow@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 12:58:24 by crenfrow          #+#    #+#             */
/*   Updated: 2016/11/17 22:58:19 by crenfrow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 16

typedef	struct	s_file
{
	char		buffer[BUFF_SIZE];
	char		*next;
	int			file_read;
	int			line_sz;
	int			status;
	int			file_desc;
}				t_file;

int				get_next_line(const int fd, char **line);

#endif
