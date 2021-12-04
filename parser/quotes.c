/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:10:50 by misha             #+#    #+#             */
/*   Updated: 2021/12/03 21:17:37 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
static char	*backslash(char *line, int *i) // любые символы или только спец?
{
	char	*first;
	char	*second;
	char	*final;

	first = ft_substr(line, 0, *i);
	second = ft_strdup(&line[*i + 1]);
	final = ft_strjoin(first, second);
	free(first);
	free(second);
	return (final);
}
*/

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

static char	*single_quot(char *line, int *i)
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

static char	*double_quot(char *line, int *i, char **env)
{
	int		begin;
	char	*new_line;

	begin = *i;
	(*i)++;
	while (line[*i] && line[*i + 1] && line[*i] != '\"')
	{
		// if (line[*i] == '\\' && (line[*i + 1] == '\\' || \
		// 	line[*i + 1] == '\'' || line[*i + 1] == '$'))
		// 	line = backslash(line, i);
		if (line[*i] == '$' && (line[*i + 1] == '_' || ft_isalpha(line[*i + 1])))
			line = env_replace(line, i, env);
		(*i)++;
	}
	new_line = remove_quotes(line, begin, i);
	return (new_line);
}

char	*parse_line(char *line_const, char **env)
{
	int		i;
	char	*line;

	i = 0;
	line = ft_strdup(line_const);
	while (line[i])
	{
		if (line[i] == '\"')
			line = double_quot(line, &i, env);
		if (line[i] == '\'')
			line = single_quot(line, &i);
		// if (line[i] == '\\')
		// 	line = backslash(line, &i);
		if (line[i] == '$' && (line[i + 1] == '_' || ft_isalpha(line[i + 1])))
			line = env_replace(line, &i, env);
		i++;
	}
	return (line);
}