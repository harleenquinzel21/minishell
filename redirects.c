/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:41:57 by ogarthar          #+#    #+#             */
/*   Updated: 2022/01/07 20:29:31 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_fd(int file, t_arg *data)
{
	int	fd;

	fd = dup(STDOUT_FILENO);
	if (fd == -1)
	{
		close(file);
		ft_exit(errno, "dup", data);
	}
	if (dup2(file, STDOUT_FILENO) == -1)
	{
		close(file);
		close(fd);
		ft_exit(errno, "dup2", data);
	}
	return (fd);
}

int	dup_cmd(t_command *cmd, t_arg *data)
{
	int		fd;
	int		file;
	t_redir	*temp;

	temp = cmd->out;
	if (!cmd->out)
		return (-1);
	while (cmd->out)
	{
		if (cmd->out->two == 1)
			file = open(cmd->out->name, O_RDWR | O_CREAT | O_APPEND, 0777);
		else
			file = open(cmd->out->name, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (file == -1)
			ft_exit(errno, cmd->out->name, data);
		if (cmd->out->target == 1)
			fd = dup_fd(file, data);
		close(file);
		cmd->out = cmd->out->next;
	}
	cmd->out = temp;
	return (fd);
}

void	redup_cmd(int fd, t_arg *data)
{
	int	i;

	(void)data;
	if (fd == -1)
		return ;
	i = dup2(fd, STDOUT_FILENO);
	if (i == -1)
	{
		close(fd);
		ft_exit(errno, "dup2", data);
	}
	close(fd);
	return ;
}
