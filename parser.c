/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:09:43 by fbeatris          #+#    #+#             */
/*   Updated: 2021/11/28 20:50:46 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
незакрытые кавычки, незакрытые двойные, бэкслэш в конце,
два пайпа подряд, что еще?
*/
/*
int	unclosed_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			
	}
	return (0);
}

int	check_syntax(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		
	}
	return (0);
}
*/

static char	*replace_str(char *line, char *old, char *new)
{
	int		i;
	int		j;
	int		k;
	char	*result;
	int		res_len;

	i = 0;
	j = 0;
	k = 0;
	res_len = ft_strlen(line) - ft_strlen(old) + ft_strlen(new);
	result = malloc(sizeof(*line) * res_len);
	while (i < res_len && ft_strncmp(&line[i + 1], old, ft_strlen(old)))
	{
		result[i] = line[i];
		i++;
	}
	k = i + ft_strlen(old) + 1;
	while (new[j])
		result[i++] = new[j++];
	while (line[k])
		result[i++] = line[k++];
	result[i] = '\0';
	return (result);
}

static char	*env_replace(char *line, int *i, char **env)
{
	int		begin;
	char	*env_key;
	char	*env_value;
	int		j;
	int		key_len;

	begin = *i;
	(*i)++;
	while (line[*i] && (line[*i] == '_' || ft_isalnum(line[*i])))
		(*i)++;
	env_key = ft_substr(line, begin + 1, *i - begin - 1);
//	printf("env key = |%s|\n", env_key);
	key_len = ft_strlen(env_key);
	j = 0;
	while (env[j])
	{
		if (ft_strncmp(env[j], env_key, key_len) == 0 && env[j][key_len] == '=')
			env_value = ft_strdup(&env[j][key_len + 1]);
		j++;
	}
//	printf("env value |%s|\n", env_value);
//	printf("Result |%s|\n", replace_str(line, env_key, env_value));
	line = replace_str(line, env_key, env_value);
	free(env_key);
	free(env_value);
	return (line);
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
	printf("single quotes res |%s|\n", new_line);
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
//	printf("double quotes res |%s|\n", new_line);
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
			line = double_quot(line, &i);
		if (line[i] == '\'')
			line = single_quot(line, &i);
		if (line[i] == '\\')
			line = backslash(line, &i);
		if (line[i] == '$' && (line[i + 1] == '_' || ft_isalpha(line[i + 1])))
			line = env_replace(line, &i, env);
//		printf("line in while %s\n", line);
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
//		if (check_syntax(line))
//			return (1);
		line = parse_line(line, envp);
		printf("line = %s\n", line);
		free(line);
	}
	return (0);
}
