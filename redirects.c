/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:41:57 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/17 15:30:00 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	dup_cmd(t_command *cmd, t_arg *data)
{
	int	fd;
	int	file;

	if (!cmd->out)
		return (0);
	if (cmd->out->two == 1)
	{
		// cmd->out->name = ft_strdup("file");
		file = open(cmd->out->name, O_RDWR | O_CREAT | O_APPEND, 0777);

	}
	else
		file = open(cmd->out->name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	printf("%s  %d %s!", cmd->cmd[0], cmd->out->two, cmd->out->name);
	if (file == -1)
	{

		ft_exit(errno, cmd->out->name, data);

	}
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
	close(file);
	return (fd);
}

void	redup_cmd(int fd, t_arg *data)
{
	(void)data;

	int i;
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
