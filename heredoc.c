/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:29:07 by ogarthar          #+#    #+#             */
/*   Updated: 2022/01/06 20:55:42 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	g_ex = 0;

void	heredoc_sig_int(int sig)
{
	(void)sig;
	// rl_clear_history();
	// ft_putchar_fd('\n', STDERR_FILENO);
	// // rl_on_new_line();
	// rl_redisplay();
//	write(1, "  \b\b\n", 5);
	// rl_on_new_line();
	// // rl_replace_line("", 1);
	// // rl_redisplay();
	printf("\033[1F                 !");
	ft_exit(1, NULL, NULL);
}

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
		if (!*end)
		{
			*line = NULL;
			return;
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

void	heredoc(char *name, char *limiter, t_arg *data)
{
	char	*line;
	int		fd;
	int		i = 1;
	int	status;
	pid_t	pid;

	pid = fork();///

	if (pid == -1)
	{
		data->errnum = errno;
		waitpid(pid, &status, 0);
		ft_exit(data->errnum, "fork", data);
	}
	if (pid == 0)
	{

		fd = open(name, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0644);
		if (fd == -1)
			ft_exit(errno, name, data);
		i = 1;
		while (i)
		{
			signal(SIGINT, &heredoc_sig_int);
			// if (g_ex == 1)
			// {
			// 	// printf("!!\n");
			// 	// line = ft_strdup(limiter, data);
			// 	// line = ft_strdup("\n", data);
			// 	g_ex = 0;
			// 	break;
			// }
			write(1, "> ", 2);

			gnl(&line, data);
			if (!line)
			{
				write(1, "  \b\b", 1);
				break;
			}

			if (ft_strcmp(line, limiter))
				write_file(name, fd, line, data);
			else
				i = 0;
			free(line);

		}
	// g_ex = 0;
	close(fd);
	}

	waitpid(pid, &status, 0);
}
