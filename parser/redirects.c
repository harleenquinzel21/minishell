/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 22:19:52 by fbeatris          #+#    #+#             */
/*   Updated: 2021/12/17 17:59:26 by ogarthar         ###   ########.fr       */
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
}

void	add_out_redir(char *line, int *i, t_arg *data)
{
	t_redir *temp;
	int		save_i;

	save_i = *i;
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
	if (line[save_i] == '>' && line[save_i + 1] != '>')
		data->cmd->out->two = 0;
	else if (line[save_i] == '>' && line[save_i + 1] == '>')
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
