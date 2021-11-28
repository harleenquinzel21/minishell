/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:09:43 by fbeatris          #+#    #+#             */
/*   Updated: 2021/11/28 17:30:45 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
незакрытые кавычки, незакрытые двойные, бэкслэш в конце,
два пайпа подряд, что еще?
*/
int	check_syntax(char *line)
{
	(void)line;
	return (0);
}

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

static char	*double_quot(char *line, int *i)
{
	int		begin;
	char	*new_line;

	begin = *i;
	(*i)++;
	while (line[*i] && line[*i + 1] && line[*i] != '\"')
	{
		if (line[*i] == '\\' && (line[*i + 1] == '\\' || \
			line[*i + 1] == '\'' || line[*i + 1] == '$'))
			line = backslash(line, i);
		(*i)++;
	}
	new_line = remove_quotes(line, begin, i);
	return (new_line);
}

char	*parse_line(char *line_const)
{
	int		i;
	char	*line;

	i = 0;
	line = ft_strdup(line_const);
	while (line[i])
	{
		if (line[i] == '\'')
			line = single_quot(line, &i);
		if (line[i] == '\"')
			line = double_quot(line, &i);
		if (line[i] == '\\')
			line = backslash(line, &i);
		i++;
	}
//	printf("%s\n", line);
	return (line);
}

int	parser(int ac, char **av, char **envp) // ctrl-D, ctrl+C, ctrl+slash
{
	char	*line;

	(void)ac;
	(void)av;
	(void)envp;
	line = NULL;

	while (1)
	{
		line = readline("\033[1;35m>>>\033[0;37m");
		if (line && *line)
			add_history(line);
		if (check_syntax(line))
			return (1);
		line = parse_line(line);
		printf("%s\n", line);
		free(line);
	}
	return (0);
}
