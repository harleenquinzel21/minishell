/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 22:19:52 by fbeatris          #+#    #+#             */
/*   Updated: 2021/12/26 17:34:06 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_in_redir(char *line, int *i, t_command *cmd, t_arg *data)
{
	t_redir	*temp;

	temp = cmd->in;
	if (cmd->in == NULL)
	{
		cmd->in = new_redir(line, i, data);
		cmd->in->target = 1;
	}
	else
	{
		while (cmd->in->next)
			cmd->in = cmd->in->next;
		cmd->in->next = new_redir(line, i, data);
		cmd->in->next->target = 1;
		cmd->in->target = 0;
		cmd->in = temp;
	}
}

void	add_out_redir(char *line, int *i, t_command *cmd, t_arg *data)
{
	t_redir	*temp;

	temp = cmd->out;
	if (cmd->out == NULL)
	{
		cmd->out = new_redir(line, i, data);
		cmd->out->target = 1;
	}
	else
	{
		while (cmd->out->next)
			cmd->out = cmd->out->next;
		cmd->out->next = new_redir(line, i, data);
		cmd->out->next->target = 1;
		cmd->out->target = 0;
		cmd->out = temp;
	}
}

char	*parse_redirects(char *line, int *i, t_command *cmd, t_arg *data)
{
	if (line[*i] && line[*i] == '>')
		add_out_redir(line, i, cmd, data);
	else if (line[*i] && line[*i] == '<')// && line[*i + 1] != '<')
		add_in_redir(line, i, cmd, data);
	return (line);
}
