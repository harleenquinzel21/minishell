/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:10:50 by misha             #+#    #+#             */
/*   Updated: 2022/01/02 20:18:06 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_quotes(char *line, int begin, int *i)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(line);
	while (begin + j < *i - 1)
	{
		line[begin + j] = line[begin + j + 1];
		j++;
	}
	while (begin + j < len)
	{
		line[begin + j] = line[begin + j + 2];
		j++;
	}
	while (line[begin + j + 2])
		line[begin + j + 2] = '\0';
}

char	*single_quotes(char *line, int *i, t_arg *data)
{
	int		begin;

	(void) data;
	begin = *i;
	(*i)++;
	while (line[*i] && line[*i + 1] && line[*i] != '\'')
		(*i)++;
	remove_quotes(line, begin, i);
	return (line);
}

char	*double_quotes(char *line, int *i, t_env *envp, t_arg *data)
{
	int		begin;

	begin = *i;
	(*i)++;
	while (line[*i] && line[*i + 1] && line[*i] != '\"')
	{
		if (line[*i] == '$' && (line[*i + 1] == '_' || \
			ft_isalpha(line[*i + 1])))
			line = env_replace(line, i, envp, data);
		(*i)++;
	}
	remove_quotes(line, begin, i);
	return (line);
}
