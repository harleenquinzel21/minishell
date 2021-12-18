/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:51:22 by fbeatris          #+#    #+#             */
/*   Updated: 2021/12/18 03:20:40 by fbeatris         ###   ########.fr       */
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
	result = ft_substr(line, begin, *i - begin);
	remove_redirect(line, save, *i);
	*i = save;
	return (result);
}

t_redir	*new_redir(char *line, int *i)
{
	t_redir *new;

	new = malloc(sizeof(t_redir));
	if (line[*i + 1] && line[*i + 1] == '>')
	{
		new->name = save_redir_name(line, i);
		new->two = 1;
		(*i)++;
	}
	else
	{
		new->name = save_redir_name(line, i);
		new->two = 0;	
	}
	
	new->next = NULL;	
	return (new);
}
