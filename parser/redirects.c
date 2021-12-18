/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 22:19:52 by fbeatris          #+#    #+#             */
/*   Updated: 2021/12/18 03:32:29 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_in_redir(char *line, int *i, t_arg *data)
{
	t_redir *temp;

	temp = data->cmd->in;
	if (data->cmd->in == NULL)
	{
		data->cmd->in = new_redir(line, i);
		data->cmd->in->target = 1;
	}
	else
	{
		while (data->cmd->in->next)
			data->cmd->in = data->cmd->in->next;
		data->cmd->in->next = new_redir(line, i);
		data->cmd->in->next->target = 1;
		data->cmd->in->target = 0;
		data->cmd->in = temp;
	}
}

void	add_out_redir(char *line, int *i, t_arg *data)
{
	t_redir *temp;

	temp = data->cmd->out;
	if (data->cmd->out == NULL)
	{
		data->cmd->out = new_redir(line, i);
		data->cmd->out->target = 1;
	}
	else
	{
		while (data->cmd->out->next)
			data->cmd->out = data->cmd->out->next;
		data->cmd->out->next = new_redir(line, i);
		data->cmd->out->next->target = 1;
		data->cmd->out->target = 0;
		data->cmd->out = temp;
	}
}

void	read_here_doc(char *line, int *i, t_arg *data)
{
	(void)line;
	(void)data;
	(*i)++;
	printf("¯\\_(ツ)_/¯   Ooops, \'<<\' not ready yet   :)\n");
}

char	*parse_redirects(char *line, int *i, t_arg *data)
{
	if (line[*i] == '>')
		add_out_redir(line, i, data);
	else if (line[*i] == '<' && line[*i + 1] != '<')
		add_in_redir(line, i, data);
	else if (line[*i] == '<' && line[*i + 1] == '<')
		read_here_doc(line, i, data);
	// printf("redir line |%s|\n", line);
	return (line);
}
