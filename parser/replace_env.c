/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:21:14 by misha             #+#    #+#             */
/*   Updated: 2022/01/07 20:13:40 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*replace_str(char *line, char *old, char *new, int start)
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
	while (i < res_len && i < start)
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

char	*env_replace(char *line, int *i, t_env *envp, t_arg *data)
{
	int		begin;
	char	*env_key;
	char	*env_value;
	t_env	*temp;

	begin = *i;
	env_value = ft_strdup("", data);
	(*i)++;
	while (line[*i] && (line[*i] == '_' || ft_isalnum(line[*i])))
		(*i)++;
	env_key = ft_substr(line, begin + 1, *i - begin - 1, data);
	temp = envp;
	while (temp)
	{
		if (ft_strcmp(temp->key, env_key) == 0)
		{
			free(env_value);
			env_value = temp->value;
		}
		temp = temp->next;
	}
	line = replace_str(line, env_key, env_value, begin);
	*i = begin + ft_strlen(env_value) - 1;
	free(env_key);
	return (line);
}

char	*exit_code_replace(char *line, t_arg *data, int *i)
{
	char	*exit_code;

	exit_code = ft_itoa(data->errnum, data);
	line = replace_str(line, "?", exit_code, *i);
	return (line);
}
