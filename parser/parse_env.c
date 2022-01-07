/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 23:03:14 by fbeatris          #+#    #+#             */
/*   Updated: 2022/01/07 20:26:30 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_create_new(char *key, char *sep, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->key = key;
	new->separator = sep;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	env_add_new(char *env_line, t_env **first, t_arg *data)
{
	t_env	*tmp;
	char	*key;
	char	*sep;
	char	*value;
	int		i;

	i = 0;
	sep = NULL;
	value = NULL;
	while (env_line[i] && (env_line[i] == '_' || ft_isalnum(env_line[i])))
		i++;
	key = ft_substr(env_line, 0, i, data);
	if (ft_strchr(env_line, '='))
		sep = ft_substr(env_line, i, 1, data);
	if (env_line[i + 1])
		value = ft_strdup(&env_line[i + 1], data);
	if (*first == NULL)
		*first = env_create_new(key, sep, value);
	else
	{
		tmp = *first;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = env_create_new(key, sep, value);
	}
}

void	add_current_path(t_arg *data)
{
	t_env	*temp;
	char	*pwd;
	char	*temp_path;
	char	*new_path;

	temp = data->envp;
	while (ft_strcmp(temp->key, "PWD") != 0)
		temp = temp->next;
	pwd = temp->value;
	temp = data->envp;
	while (ft_strcmp(temp->key, "PATH") != 0)
		temp = temp->next;
	temp_path = ft_strjoin(temp->value, ":", data);
	new_path = ft_strjoin(temp_path, pwd, data);
	free(temp->value);
	temp->value = ft_strdup(new_path, data);
	free(temp_path);
	free(new_path);
}

void	parse_env(char **envp, t_arg *data)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		env_add_new(envp[i], &data->envp, data);
		i++;
	}
	add_current_path(data);
}
