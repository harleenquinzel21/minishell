/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:06:22 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/12 15:10:12 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_search_dups(t_env *envp, char *new, int i, char *newkey)
{
	char	*newvalue;

	if (ft_strchr(new, '+') && (ft_export_join(new, envp)))
		return (1);
	while (new[i] && (new[i] == '_' || ft_isalnum(new[i])))
		i++;
	newkey = ft_substr(new, 0, i);
	newvalue = ft_strdup(&new[i + 1]);
	while (envp)
	{
		if (!(ft_strcmp(envp->key, newkey)))
		{
			if (envp->value)
				envp->value = NULL;
			envp->value = ft_strdup(newvalue);
			free(newkey);
			free(newvalue);
			return (1);
		}
		else
			envp = envp->next;
	}
	free(newkey);
	free(newvalue);
	return (0);
}

int	if_without_arg(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->separator[0])
			printf("declare -x %s%s\"%s\"\n", tmp->key, \
					tmp->separator, tmp->value);
		else
			printf("declare -x %s%s%s\n", tmp->key, \
					tmp->separator, tmp->value);
		tmp = tmp->next;
	}
	return (1);
}

void	ft_export_unset_error(t_arg *data, char *str, char *namecmd)
{
	data->errnum = 1;
	ft_putstr_fd(namecmd, 2);
	write(2, ": `", 3);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
}

int	ft_export_join(char *new, t_env *envp)
{
	char	*newkey;
	char	*newvalue;
	int		i;

	i = 0;
	while (new[i] && (new[i] == '_' || ft_isalnum(new[i])))
		i++;
	if (new[i] != '+' && new[i + 1] != '=')
		return (0);
	newkey = ft_substr(new, 0, i);
	newvalue = ft_strdup(&new[i + 2]);
	while (envp)
	{
		if (!(ft_strcmp(envp->key, newkey)))
		{
			envp->value = ft_strjoin(envp->value, &new[i + 2]);
			break;
		}
		else
			envp = envp->next;
	}
	free(newkey);
	free(newvalue);
	return (1);
}

int	ft_export(t_arg *data)
{
	char	*newkey;
	int		i;
	int		j;

	i = 1;
	j = 0;
	newkey = NULL;
	data->errnum = 0;
	if (!data->cmd->cmd[1])
		return (if_without_arg(data->envp));
	while (data->cmd->cmd[i])
	{
		if (ft_isalpha(data->cmd->cmd[i][0]) && \
			ft_strchr(data->cmd->cmd[i], '='))
		{
			if (ft_search_dups(data->envp, data->cmd->cmd[i], j, newkey))
				return (1);
			env_add_new(data->cmd->cmd[i], &data->envp);
		}
		else
			ft_export_unset_error(data, data->cmd->cmd[i], "export");
		i++;
	}
	return (1);
}
