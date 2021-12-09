/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:06:22 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/09 16:52:51 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_search_dups(t_env *envp, char *new, int i)
{
	t_env	*tmp;
	char	*newkey;
	char	*newvalue;

	tmp = envp;
	while (new[i] && (new[i] == '_' || ft_isalnum(new[i])))
		i++;
	newkey = ft_substr(new, 0, i);
	newvalue = ft_strdup(&new[i + 1]);
	while (tmp)
	{
		if (!(ft_strcmp(tmp->key, newkey)))
		{
			if (tmp->value)
				tmp->value = NULL;
			tmp->value = ft_strdup(newvalue);
			return (1);
		}
		else
			tmp = tmp->next;
	}
	free(newkey);
	free(newvalue);
	return (0);
}

static int	if_without_arg(t_env *env)
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

void	ft_expor_unset_error(t_arg *data, char *str, char *namecmd)
{
	data->errnum = 1;
	ft_putstr_fd(namecmd, 2);
	write(2, ": `", 3);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
}

int	ft_export(t_arg *data)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	data->errnum = 0;
	if (!data->cmd->cmd[1])
		return (if_without_arg(data->envp));
	while (data->cmd->cmd[i])
	{
		if (ft_isalpha(data->cmd->cmd[i][0]) && \
			ft_strchr(data->cmd->cmd[i], '='))
		{
			if (ft_search_dups(data->envp, data->cmd->cmd[i], j))
				return (1);
			env_add_new(data->cmd->cmd[i], &data->envp);
		}
		else
			ft_expor_unset_error(data, data->cmd->cmd[i], "export");
		i++;
	}
	return (1);
}
