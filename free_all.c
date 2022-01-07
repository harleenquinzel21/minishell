/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:35:44 by ogarthar          #+#    #+#             */
/*   Updated: 2022/01/07 18:50:22 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir_env_fd(t_arg *data)
{
	int		i;
	t_redir	*redir_temp;

	while (data->redir)
	{
		redir_temp = data->redir->data_next;
		if (data->redir->in && data->redir->two)
		{
			unlink(data->redir->name);
			free(data->redir->limiter);
		}
		free(data->redir->name);
		free(data->redir);
		data->redir = redir_temp;
	}
	i = 0;
	while (data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	free (data->env);
	if (data->num > 1)
		free(data->fd);
}

void	free_commands(t_arg *data)
{
	int	i;

	i = 0;
	if (data->cmd->cmd && data->cmd->cmd[0] && \
		ft_strcmp(data->cmd->cmd[0], "cd") == 0 && \
		ft_strcmp(data->cmd->cmd[1], "~") == 0)
	{
		free(data->cmd->cmd[0]);
		free(data->cmd->cmd[1]);
	}
	else
	{
		while (data->cmd->cmd[i])
		{
			free(data->cmd->cmd[i]);
			i++;
		}
	}
}

void	free_structs(t_arg *data)
{
	t_command	*cmd_temp;

	while (data->cmd)
	{
		cmd_temp = data->cmd->next;
		free_commands(data);
		free(data->cmd->cmd);
		free(data->cmd);
		data->cmd = cmd_temp;
	}
	free_redir_env_fd(data);
}
