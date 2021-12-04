/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:21:14 by misha             #+#    #+#             */
/*   Updated: 2021/12/03 21:17:39 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*env_replace(char *line, int *i, char **env)
{
	int		begin;
	char	*env_key;
	char	*env_value;
	int		j;
	int		key_len;

	begin = *i;
	env_value = ft_strdup("");
	(*i)++;
	while (line[*i] && (line[*i] == '_' || ft_isalnum(line[*i])))
		(*i)++;
	env_key = ft_substr(line, begin + 1, *i - begin - 1);
	key_len = ft_strlen(env_key);
	j = 0;
	while (env[j])
	{
		if (ft_strncmp(env[j], env_key, key_len) == 0 && env[j][key_len] == '=')
			env_value = ft_strdup(&env[j][key_len + 1]);
		j++;
	}
	line = replace_str(line, env_key, env_value);		
	free(env_key);
	free(env_value);
	return (line);
}
