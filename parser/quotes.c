/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:10:50 by misha             #+#    #+#             */
/*   Updated: 2021/12/25 23:02:22 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*remove_quotes(char *line, int begin, int *i)
{
	char	*first;
	char	*second;
	char	*third;
	char	*pre_final;
	char	*final;

	first = ft_substr(line, 0, begin);
	second = ft_substr(line, begin + 1, *i - begin - 1);
	third = ft_strdup(&line[*i + 1]);
	pre_final = ft_strjoin(first, second);
	final = ft_strjoin(pre_final, third);
	free(first);
	free(second);
	free(third);
	free(pre_final);
	free(line);
	return (final);
}

char	*single_quotes(char *line, int *i)
{
	int		begin;
	char	*new_line;

	begin = *i;
	(*i)++;
	while (line[*i] && line[*i + 1] && line[*i] != '\'')
		(*i)++;
	new_line = remove_quotes(line, begin, i);
	return (new_line);
}

char	*double_quotes(char *line, int *i, t_env *envp)
{
	int		begin;
	char	*new_line;

	begin = *i;
	(*i)++;
	while (line[*i] && line[*i + 1] && line[*i] != '\"')
	{
		if (line[*i] == '$' && (line[*i + 1] == '_' || \
			ft_isalpha(line[*i + 1])))
			line = env_replace(line, i, envp);
		(*i)++;
	}
	new_line = remove_quotes(line, begin, i);
	return (new_line);
}
