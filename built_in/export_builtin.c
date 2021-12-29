/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:06:22 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/29 20:31:47 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	ft_search_dups(t_env *envp, char *new, int i, t_arg *data)
{
	// char	*newvalue;
	char	*newkey;

	while (new[i] && (new[i] == '_' || ft_isalnum(new[i])))
		i++;
	newkey = ft_substr(new, 0, i, data);
	// newvalue = ft_strdup(&new[i + 1], data);
	while (envp)
	{
		if (!(ft_strcmp(envp->key, newkey)))
		{
			if (envp->value)
				envp->value = NULL;
			envp->value = ft_strdup(&new[i + 1], data);
			free(newkey);
			// free(newvalue);
			return (1);
		}
		else
			envp = envp->next;
	}
	free(newkey);
	// free(newvalue);
	return (0);
}

int	if_without_arg(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->separator && tmp->value)
			printf("declare -x %s%s\"%s\"\n", tmp->key, \
					tmp->separator, tmp->value);
		else if (tmp->separator)
			printf("declare -x %s%s\"\"\n", tmp->key, \
					tmp->separator);
		else
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_export_join(char *new, t_env *envp, t_arg *data)
{
	char	*newkey;
	char	*newvalue;
	int		i;

	i = 0;
	while (new[i] && (new[i] == '_' || ft_isalnum(new[i])))
		i++;
	if (new[i] != '+' && new[i + 1] != '=')
		return (0);
	newkey = ft_substr(new, 0, i, data);
	newvalue = ft_strdup(&new[i + 2], data);
	while (envp)
	{
		if (!(ft_strcmp(envp->key, newkey)))
		{
			envp->value = ft_strjoin(envp->value, newvalue, data);
			return (1);
		}
		// else
		envp = envp->next;
	}
	free(newkey);
	free(newvalue);
	return (0);
}

int	ft_add_new(char	*new, t_arg *data)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	while (new[i] && (new[i] == '_' || ft_isalnum(new[i])))
		i++;
	if (new[i] != '+')
		return (0);
	line = ft_substr(new, 0, i, data);
	line = ft_strjoin(line, "=", data);
	line = ft_strjoin(line, &new[i + 2], data);
	env_add_new(line, &data->envp, data);
	free(line);
	return (1);
}

int	ft_export(t_arg *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->errnum = 0;
	if (!data->cmd->cmd[1])
		return (if_without_arg(data->envp));
	while (data->cmd->cmd[++i])
	{
		if (ft_isalpha(data->cmd->cmd[i][0]))
		{
			if (ft_strchr(data->cmd->cmd[i], '+') && \
				ft_strchr(data->cmd->cmd[i], '=') && \
				(ft_export_join(data->cmd->cmd[i], data->envp, data)))
				continue;
			if (ft_search_dups(data->envp, data->cmd->cmd[i], j, data))
				continue;
			if (!ft_add_new(data->cmd->cmd[i], data))
				env_add_new(data->cmd->cmd[i], &data->envp, data);
		}
		else
			ft_export_unset_error(data, data->cmd->cmd[i], "export");
	}
	return (data->errnum);
}
