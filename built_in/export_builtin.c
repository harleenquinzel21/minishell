/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:06:22 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/08 21:52:06 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

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

void	free_new(t_env *new)
{
	t_env	*tmp;

	while (new)
	{
		tmp = new;
		new = new->next;
		free(tmp->key);
		free(tmp->separator);
		free(tmp->value);
		free(tmp);
	}
}

int	ft_search_dups(t_env *envp, char *new, t_arg *data)
{
	t_env	*tmp;
	int		len;
	int stpncmp = 0;

	(void)data;
	tmp = envp;
	len = ft_strlen(tmp->key);
	stpncmp = ft_strncmp(new, tmp->key, len - 1);
	printf("%d", stpncmp);
		while (tmp)
		{
			if (!stpncmp)
			{
				if (new[len + 1] && !tmp->separator[0])
				{
					tmp->separator = NULL;
					tmp->separator = ft_strdup("=");
				}
				tmp->value = NULL;
				tmp->value = ft_strdup(&new[len + 2]);
				return(1);
			}
			else
				tmp = tmp->next;
		}
		// if (!tmp2)
		// 	ft_env_lst_add_back(&envp, ft_one_lst(new, data));
		// new = new->next;
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



int	ft_export(t_arg *data)
{
	int		i;
	t_env	*new;

	data->errnum = 0;
	i = 1;
	new = NULL;
	if (!data->cmd->cmd[1])
		return (if_without_arg(data->envp));

	while (data->cmd->cmd[i])///добавление элемента в конец списка
	{
		if (ft_isalpha(data->cmd->cmd[i][0]) && ft_strchr(data->cmd->cmd[i], '='))
		{
			if (ft_search_dups(data->envp, data->cmd->cmd[i], data))
				return (1);
			env_add_new(data->cmd->cmd[i], &data->envp);
		}
		else
		{
			data->errnum = 1;
			write(2, "export: `", 9);
			write(2, data->cmd->cmd[i], ft_strlen(data->cmd->cmd[i]));
			write(2, "': not a valid identifier\n", 26);
		}
		i++;
	}


	free_new(new);
	return (1);
}
