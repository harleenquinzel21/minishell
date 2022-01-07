/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:51:22 by fbeatris          #+#    #+#             */
/*   Updated: 2022/01/07 20:34:47 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_redirect(char *line, int start, int end)
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
	while (line[start + i + 1])
	{
		line[start + i + 1] = '\0';
		i++;
	}
}

char	*save_redir_name(char *line, int *i, t_arg *data)
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
	while (line[*i] && line[*i] != ' ' && line[*i] != '|')
		(*i)++;
	result = ft_substr(line, begin, *i - begin, data);
	remove_redirect(line, save, *i);
	*i = save;
	return (result);
}

void	data_redir_list(t_redir *new, t_arg *data)
{
	t_redir	*temp;

	temp = data->redir;
	if (data->redir == NULL)
	{
		data->redir = new;
		data->redir->cmd = 1;
		if (data->redir->in && data->redir->two)
			data->redir->name = ft_strjoin("heredoc", "1", data);
		if (data->redir->name == NULL)
			ft_exit(12, "malloc", data);
	}
	else
	{
		while (data->redir->data_next)
			data->redir = data->redir->data_next;
		data->redir->data_next = new;
		data->redir->data_next->cmd = data->num_cmd;
		if (data->redir->data_next->in && data->redir->data_next->two)
			data->redir->data_next->name = ft_strjoin("heredoc", \
				ft_itoa(data->redir->data_next->cmd, data), data);
		if (data->redir->name == NULL)
			ft_exit(12, "malloc", data);
		data->redir = temp;
	}
}
