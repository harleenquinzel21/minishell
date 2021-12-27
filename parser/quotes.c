/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:10:50 by misha             #+#    #+#             */
/*   Updated: 2021/12/27 16:22:11 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*remove_quotes(char *line, int begin, int *i, t_arg *data)
{
	char	*first;
	char	*second;
	char	*third;
	char	*pre_final;
	char	*final;

	first = ft_substr(line, 0, begin, data);
	second = ft_substr(line, begin + 1, *i - begin - 1, data);
	third = ft_strdup(&line[*i + 1], data);
	pre_final = ft_strjoin(first, second, data);
	final = ft_strjoin(pre_final, third, data);
	free(first);
	free(second);
	free(third);
	free(pre_final);
	free(line);
	return (final);
}

char	*single_quotes(char *line, int *i, t_arg *data)
{
	int		begin;
	char	*new_line;

	begin = *i;
	(*i)++;
	while (line[*i] && line[*i + 1] && line[*i] != '\'')
		(*i)++;
	new_line = remove_quotes(line, begin, i, data);
	return (new_line);
}

char	*double_quotes(char *line, int *i, t_env *envp, t_arg *data)
{
	int		begin;
	char	*new_line;

	begin = *i;
	(*i)++;
	while (line[*i] && line[*i + 1] && line[*i] != '\"')
	{
		if (line[*i] == '$' && (line[*i + 1] == '_' || \
			ft_isalpha(line[*i + 1])))
			line = env_replace(line, i, envp, data);
		(*i)++;
	}
	new_line = remove_quotes(line, begin, i, data);
	return (new_line);
}
