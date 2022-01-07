/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:30:03 by ogarthar          #+#    #+#             */
/*   Updated: 2022/01/07 20:16:45 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(t_arg *data, int *file, int num)
{
	int	i;

	i = -1;
	while (++i < num)
	{
		if (!data->fd || !data->fd[i])
			continue ;
		close(data->fd[i][0]);
		close(data->fd[i][1]);
		free(data->fd[i]);
	}
	if (!file)
		return ;
	if (file[0])
		close(file[0]);
	if (file[1])
		close(file[1]);
}

void	ft_dup2(int i, int *file, t_command *cmd, t_arg *data)
{
	int	dup2res;

	dup2res = 0;
	if (cmd->in)
		dup2res = dup2(file[0], STDIN_FILENO);
	else if (i && data->fd)
		dup2res = dup2(data->fd[i - 1][0], STDIN_FILENO);
	if (dup2res == -1)
		ft_exit(errno, "dup2", data);
	if (cmd->out)
		dup2res = dup2(file[1], STDOUT_FILENO);
	else if (i < data->num - 1 && data->fd)
		dup2res = dup2(data->fd[i][1], STDOUT_FILENO);
	if (dup2res == -1)
		ft_exit(errno, "dup2", data);
	ft_close(data, file, data->num - 1);
}

static void	ft_waitpid(pid_t *pid, int num, t_arg *data)
{
	int	i;
	int	status;

	i = -1;
	while (++i < num)
		waitpid(-1, &status, 0);
	if (data)
	{
		if (WIFEXITED(status))
			data->errnum = WEXITSTATUS(status);
		else
			data->errnum = status + 128;
	}
	free(pid);
}

void	sig_pipex(void)
{
	signal(SIGINT, &sig_handler_child);
	signal(SIGQUIT, &sig_handler_child);
}

void	pipex(t_arg *data)
{
	pid_t	*pid;
	int		i;

	pid = malloc(data->num * sizeof(pid_t));
	if (!pid)
		ft_exit(errno, "malloc", data);
	i = -1;
	while (++i < data->num)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			child_process(i, data);
		if (pid[i] == -1)
		{
			data->errnum = errno;
			ft_close(data, NULL, data->num - 1);
			ft_waitpid(pid, i, NULL);
			ft_exit(data->errnum, "fork", data);
		}
		if (pid[i] != 0)
			sig_pipex();
	}
	ft_close(data, NULL, data->num - 1);
	ft_waitpid(pid, data->num, data);
}
