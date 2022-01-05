/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:00:18 by ogarthar          #+#    #+#             */
/*   Updated: 2022/01/05 18:39:38 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_del_env(t_env *env)
{
	t_env	*tmp;

	tmp = env->next;
	env->next = tmp->next;
	free(tmp->key);
	free(tmp->separator);
	free(tmp->value);
	free(tmp);
}

int	ft_check_first(t_env **env, char *str)
{
	t_env	*tmp;

	tmp = *env;
	if (!ft_strcmp(str, tmp->key))
	{
		*env = (*env)->next;
		free(tmp->key);
		free(tmp->separator);
		free(tmp->value);
		free(tmp);
		return (1);
	}
	return (0);
}

void	ft_export_unset_error(t_arg *data, char *str, char *namecmd)
{
	data->errnum = 1;
	ft_putstr_fd(namecmd, 2);
	write(2, ": `", 3);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
}

int	ft_check_error(char *cmd, t_arg *data)
{
	int	j;

	j = 0;
	while (cmd[j])
	{
		if (!(ft_isalpha(cmd[j])) && (cmd[j] != '_'))
		{
			ft_export_unset_error(data, cmd, "unset");
			return (1);
		}
		j++;
	}
	return (0);
}

int	ft_unset(t_command *cmd, t_arg *data)
{
	int		i;
	t_env	*tmp1;
	t_env	*tmp2;

	i = 0;
	while (cmd->cmd[++i])
	{
		if (ft_check_error(cmd->cmd[i], data) || !data->envp)
			return (1);
		if (cmd->cmd[i][0] == '_')
			continue ;
		if (ft_check_first(&data->envp, cmd->cmd[i]))
			continue ;
		tmp1 = data->envp;
		tmp2 = tmp1->next;
		while (tmp2 && ft_strcmp(cmd->cmd[i], tmp2->key))
		{
			tmp1 = tmp2;
			tmp2 = tmp2->next;
		}
		if (tmp2)
			ft_del_env(tmp1);
	}
	return (0);
}
