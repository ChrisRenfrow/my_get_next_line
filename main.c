/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenfrow <crenfrow@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 14:04:01 by crenfrow          #+#    #+#             */
/*   Updated: 2016/11/17 20:58:11 by crenfrow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	(void)	argc;
	int		fs = 1;
 	//int 	i = ft_atoi(argv[2]);
	int		fd = open(argv[1], O_RDONLY);
	//int		fd2 = open(argv[2], O_RDONLY);
	char	**line = ft_memalloc(sizeof(char **));
	*line = (char *)ft_memalloc(sizeof(char) * BUFF_SIZE);
	//t_list	**root_list = (t_list **)ft_memalloc(sizeof(t_list *));
	while (fs > 0)
	{
		fs = get_next_line(fd, line);
		ft_putendl(*line);
	}
}
