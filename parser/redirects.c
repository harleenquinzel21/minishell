/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 22:19:52 by fbeatris          #+#    #+#             */
/*   Updated: 2021/12/08 23:52:51 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_redirect(char *line, int start, int end)
{
	int	len;
	int	i;

	len = end - start;
	i = 0;
	(void)line;
	while (line[end + i])
	{
		line[start + i] = line[end + i];
		i++;
	}
	line[start + i] = '\0';
	while (line[start + i])
	{
		line[start + i] = '\0';
		i++;
	}
}

static char	*save_redir_name(char *line, int *i)
{
	int		begin;
	int		save;
	int		count;
	char	*result;

	save = *i;
	count = 0;
	while (line[*i] && (line[*i] == '>' || line[*i] == '<'))
		(*i)++;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	begin = *i;
	while (line[*i] && line[*i] != ' ')
		(*i)++;
	result = ft_substr(line, begin, *i);
	remove_redirect(line, save, *i);
	*i = save;
	return (result);
}

char	*parse_redirects(char *line, int *i, t_arg *data)
{
	if (line[*i] == '>' && line[*i + 1] != '>')
	{
		data->cmd->out->limiter = ft_strdup(">");
		data->cmd->out->name = save_redir_name(line, i);
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		data->cmd->out->limiter = ft_strdup(">>");
		data->cmd->out->name = save_redir_name(line, i);
	}
	else if (line[*i] == '<' && line[*i + 1] != '<')
	{
		data->cmd->in->limiter = ft_strdup("<");
		data->cmd->in->name = save_redir_name(line, i);
	}
	return (line);
}
