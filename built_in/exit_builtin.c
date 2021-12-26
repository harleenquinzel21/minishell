/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:19:43 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/26 17:48:32 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit_cmd(t_arg *data)
{
	// printf("exit\n");
	if (data->cmd->cmd[1])
		ft_exit((unsigned char)ft_atoi(data->cmd->cmd[1]), NULL, data);
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
	// return (0);
}

void free_cmd_redir(t_arg *data)
{
	t_command	*cmd_temp;
	t_redir		*redir_temp;

	while (data->cmd)
	{
		cmd_temp = data->cmd->next;
		free(data->cmd);
		data->cmd = cmd_temp;
	}
	while (data->redir)
	{

		redir_temp = data->redir->data_next;
		if (data->redir->in && data->redir->two)
			unlink(data->redir->name);
		free(data->redir);
		data->redir = redir_temp;
	}
//	printf("free ok\n");
}
