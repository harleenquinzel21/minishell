/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:41:57 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/16 17:39:56 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// void	red_to_cmd(t_redir *red, t_command *cmd)
// {
// 	int	i;
// 	int	num;//номер команды к которой отн-ся редирект

// 	if (!cmd)
// 		return ;
// 	i = 0;
// 	while (red)
// 	{
// 		num = red->cmd;//номер команды к которой отн-ся редирект
// 		while (i < num)
// 		{
// 			cmd = cmd->next;
// 			i++;
// 		}
// 		if (red->in)//oбратный
// 			cmd->in = red;
// 		else
// 			cmd->out = red;//прямой
// 		red = red->next;
// 	}
// }

int	dup_cmd(t_command *cmd, t_arg *data)
{
	int	fd;
	int	file;

	// if (!cmd->out)
	// 	return (-1);
	if (cmd->out->two)
		file = open(cmd->out->name, O_RDWR | O_CREAT | O_APPEND, 0777);
	else
		file = open(cmd->out->name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		ft_exit(errno, cmd->out->name, data);
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
