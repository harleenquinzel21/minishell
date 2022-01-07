/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:06:22 by ogarthar          #+#    #+#             */
/*   Updated: 2022/01/07 20:31:14 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_search_dups(t_env *envp, char *new, t_arg *data)
{
	char	*newkey;
	int		i;

	i = 0;
	while (new[i] && (new[i] == '_' || ft_isalnum(new[i])))
		i++;
	newkey = ft_substr(new, 0, i, data);
	while (envp)
	{
		if (!(ft_strcmp(envp->key, newkey)))
		{
			if (envp->value)
				envp->value = NULL;
			envp->value = ft_strdup(&new[i + 1], data);
			free(newkey);
			return (1);
		}
		else
			envp = envp->next;
	}
	free(newkey);
	return (0);
}

int	if_without_arg(t_env *env, t_arg *data)
{
	t_env	*tmp;

	(void) env;
	sort_env(data);
	tmp = data->envp_alpha;
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
		tmp = tmp->alpha_next;
	}
	return (0);
}

int	ft_export_join(char *new, t_env *envp, t_arg *data)
{
	int		i;

	i = 0;
	while (new[i] && (new[i] == '_' || ft_isalnum(new[i])))
		i++;
	if (new[i] == '=')
		return (0);
	while (envp)
	{
		if (!(ft_strcmp(envp->key, ft_substr(new, 0, i, data))))
		{
			if (envp->separator)
				free(envp->separator);
			envp->separator = ft_strdup("=", data);
			if (envp->value)
				envp->value = ft_strjoin(envp->value, ft_strdup(&new[i + 2], \
				data), data);
			else
				envp->value = ft_strdup(ft_strdup(&new[i + 2], data), data);
			return (1);
		}
		envp = envp->next;
	}
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

int	ft_export(t_arg *data, t_command *cmd)
{
	int	i;

	i = 0;
	data->errnum = 0;
	if (!cmd->cmd[1])
		return (if_without_arg(data->envp, data));
	while (cmd->cmd[++i])
	{
		if (check_arg_export(cmd->cmd[i], data))
			continue ;
		if (data->num != 1)
			break ;
		if (ft_strchr(cmd->cmd[i], '+') && \
			ft_strchr(cmd->cmd[i], '=') && \
			(ft_export_join(cmd->cmd[i], data->envp, data)))
			continue ;
		if (ft_search_dups(data->envp, cmd->cmd[i], data))
			continue ;
		if (!ft_add_new(cmd->cmd[i], data))
			env_add_new(cmd->cmd[i], &data->envp, data);
	}
	return (data->errnum);
}
