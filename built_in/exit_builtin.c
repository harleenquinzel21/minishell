/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:19:43 by ogarthar          #+#    #+#             */
/*   Updated: 2022/01/02 02:57:01 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalldigit(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-')
			i++;
	while (str[++i])
	{
		if (!ft_isdigit((unsigned char)str[i]))
			return (1);
	}
	return (0);
}

int	ft_exit_cmd(t_arg *data)
{
	ft_putstr_fd("exit\n", 1);
	if (data->cmd->cmd[1] && !ft_isalldigit(data->cmd->cmd[1]))
		ft_exit((unsigned char)ft_atoi(data->cmd->cmd[1]), NULL, data);
	else if (data->cmd->cmd[1])
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(data->cmd->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_exit(255, NULL, data);
	}
	else
		ft_exit(0, NULL, data);
	return (0);
}

int	ft_exit(int errnum, char *msg, t_arg *data)
{
	char	*errmsg;

	(void)data;///
	if (msg)
	{
		errmsg = strerror(errnum);
		write(2, msg, ft_strlen(msg));
		write(2, ": ", 2);
		write(2, errmsg, ft_strlen(errmsg));
		write(2, "\n", 1);
	}
	// ft_free(data);////
	exit(errnum);
}

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

void	free_structs(t_arg *data)
{
	t_command	*cmd_temp;
	int			i;

	while (data->cmd)
	{
		cmd_temp = data->cmd->next;
		i = 0;
		while(data->cmd->cmd[i])
		{
			free(data->cmd->cmd[i]);
			i++;
		}
		free(data->cmd->cmd);
		free(data->cmd);
		data->cmd = cmd_temp;
	}
	free_redir_env_fd(data);
}
