/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 22:19:52 by fbeatris          #+#    #+#             */
/*   Updated: 2021/12/13 23:51:19 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_in_redir(char *line, int *i, t_arg *data)
{
	t_redir *temp;

	temp = data->cmd->in;
	if (data->cmd->in == NULL)
		data->cmd->in = new_redir(line, i);
	else
	{
		while (data->cmd->in)
			data->cmd->in = data->cmd->in->next;
		data->cmd->in = new_redir(line, i);
	}
	data->cmd->in->in = 1;
	if (line[*i] == '>' && line[*i + 1] != '>')
		data->cmd->in->two = 0;
	else if (line[*i] == '>' && line[*i + 1] == '>')
		data->cmd->in->two = 1;
}

void	add_out_redir(char *line, int *i, t_arg *data)
{
	t_redir *temp;

	temp = data->cmd->out;
	if (data->cmd->out == NULL)
		data->cmd->out = new_redir(line, i);
	else
	{
		while (data->cmd->out)
			data->cmd->out = data->cmd->out->next;
		data->cmd->out = new_redir(line, i);
	}
	data->cmd->out->in = 0;
	if (line[*i] == '>' && line[*i + 1] != '>')
		data->cmd->out->two = 0;
	else if (line[*i] == '>' && line[*i + 1] == '>')
		data->cmd->out->two = 1;
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
	return (line);
}
