/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:29:07 by ogarthar          #+#    #+#             */
/*   Updated: 2022/01/07 20:05:30 by ogarthar         ###   ########.fr       */
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

void	heredoc_loop(char *name, char *limiter, t_arg *data, int fd)
{
	char	*line;

	while (1)
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
		{
			if (write(fd, line, ft_strlen(line)) == -1)
				ft_exit(errno, name, data);
			if (write(fd, "\n", 1) == -1)
				ft_exit(errno, name, data);
		}
		else
			break ;
		free(line);
	}
}

static void	ft_waitpid(pid_t pid, int status, t_arg *data)
{
	waitpid(pid, &status, 0);
	if (data)
	{
		if (WIFEXITED(status))
			data->errnum = WEXITSTATUS(status);
		else
			data->errnum = 1;
	}
}

void	heredoc(char *name, char *limiter, t_arg *data)
{
	int		fd;
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
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
		ft_exit(data->errnum, NULL, data);
	}
	ft_waitpid(pid, status, data);
	signal(SIGINT, &sig_handler_parent);
}
