/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:29:07 by ogarthar          #+#    #+#             */
/*   Updated: 2022/01/02 16:42:43 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	gnl(char **line, t_arg *data)
{
	char	*end;
	char	*tmp;

	*line = ft_strdup("\0", data);
	end = ft_strdup("\0\0", data);
	if (!*line || !end)
		ft_exit(12, "malloc", data);
	while (*end != '\n')
	{
		read(0, end, 1);
		if (*end == '\n')
			break ;
		tmp = ft_strjoin(*line, end, data);
		if (!tmp)
		{
			free(end);
			ft_exit(12, "malloc", data);
		}
		free(*line);
		*line = tmp;
	}
	free(end);
}

static void	write_file(char *name, int fd, char *line, t_arg *data)
{
	if (write(fd, line, ft_strlen(line)) == -1)
		ft_exit(errno, name, data);
	if (write(fd, "\n", 1) == -1)
		ft_exit(errno, name, data);
}

void	heredoc(char *name, char *limiter, t_arg *data)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(name, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (fd == -1)
		ft_exit(errno, name, data);
	i = 1;
	while (i)
	{
		write(1, "> ", 2);
		gnl(&line, data);
		if (ft_strcmp(line, limiter))
			write_file(name, fd, line, data);
		else
			i = 0;
		free(line);
	}
	close(fd);
}
