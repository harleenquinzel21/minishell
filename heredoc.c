/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:29:07 by ogarthar          #+#    #+#             */
/*   Updated: 2022/01/07 05:08:08 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	gnl_init_strings(char **end, char **line, t_arg *data)
{
	*line = ft_strdup("\0", data);
	*end = ft_strdup("\0\0", data);
	if (!*line || !*end)
		ft_exit(12, "malloc", data);
}

static void	gnl(char **line, t_arg *data)
{
	char	*end;
	char	*tmp;

	gnl_init_strings(&end, line, data);
	while (*end != '\n')
	{
		read(0, end, 1);
		if (*end == '\n')
			break ;
		if (!*end)
		{
			*line = NULL;
			return ;
		}
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

void	heredoc_loop(char *name, char *limiter, t_arg *data, int fd)
{
	char	*line;
	int		i;

	i = 1;
	while (i)
	{
		write(1, "> ", 2);
		signal(SIGINT, &heredoc_sig_int);
		gnl(&line, data);
		if (!line)
		{
			write(1, "  \b\b", 1);
			break ;
		}
		if (ft_strcmp(line, limiter))
			write_file(name, fd, line, data);
		else
			i = 0;
		free(line);
	}
}

void	heredoc(char *name, char *limiter, t_arg *data)
{
	int		fd;
	int		status;
	pid_t	pid;

	pid = fork();///
	if (pid == -1)
	{
		data->errnum = errno;
		waitpid(pid, &status, 0);
		ft_exit(data->errnum, "fork", data);
	}
	if (pid != 0)
		signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		fd = open(name, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0644);
		if (fd == -1)
			ft_exit(errno, name, data);
		heredoc_loop(name, limiter, data, fd);
		close(fd);
		ft_exit(data->errnum, NULL, data); // правильные аргументы ????
	}
	waitpid(pid, &status, 0);
	signal(SIGINT, &sig_handler_parent);
}
