/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenfrow <crenfrow@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 12:50:29 by crenfrow          #+#    #+#             */
/*   Updated: 2016/11/04 03:00:12 by crenfrow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int		get_next_line(const int fd, char **line)
{
	static t_file	*file;
	int i;
	int fs;

	i = 0;
	fs = 1;
	if (!file)
		file = (t_file *)ft_memalloc(sizeof(t_file));
	while (fs > 0)
	{
		fs = read(fd, file->buffer, BUFF_SIZE);
		while (file->buffer[i] != '\n' && i <= BUFF_SIZE)
			i++;
		ft_putendl(ft_itoa(i));
		if (i <= BUFF_SIZE && file->buffer[i] == '\n')
		{
			if (i == BUFF_SIZE)
				return (1);
			*line = ft_strjoin(*line, ft_strsub(file->buffer, 0, i));
		}
		else
		{
			*line = ft_strjoin(*line, file->buffer);
		}
		i = 0;
	}
	return (0);
}

/*
**==============================[DELET THIS]====================================
*/
int	main(int argc, char **argv)
{
	(void)	argc;
	int		fs = 1;
	int		fd = open(argv[1], O_RDONLY);
	//int		fd2 = open(argv[2], O_RDONLY);
	char	**line = ft_memalloc(sizeof(char **));
	*line = (char *)ft_memalloc(sizeof(char) * BUFF_SIZE);
	//t_list	**root_list = (t_list **)ft_memalloc(sizeof(t_list *));

	while (fs > 0)
	{
		fs = get_next_line(fd, line);
		ft_putendl(*line);
		//ft_putstr(*line);
		/*
		fs = get_next_line(fd2, line);
		ft_putendl(*line);
		*/
	}
}
