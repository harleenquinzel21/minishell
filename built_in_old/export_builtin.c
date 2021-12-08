/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:06:22 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/06 20:41:04 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	ft_search_dups(t_env *env, t_env *new, t_arg *data)
{
	t_env	*tmp2;

	while (new)
	{
		tmp2 = env;
		while (tmp2)
		{
			if (!ft_strcmp(new->key, tmp2->key))
			{
				if (new->separator[0] && !tmp2->separator[0])
				{
					free(tmp2->separator);
					tmp2->separator = ft_strdup_pars(new->separator, data);
				}
				free(tmp2->value);
				tmp2->value = ft_strdup_pars(new->value, data);
				break ;
			}
			else
				tmp2 = tmp2->next;
		}
		if (!tmp2)
			ft_env_lst_add_back(&env, ft_one_lst(new, data));
		new = new->next;
	}
}

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

int	ft_export(t_arg *data)
{
	int		i;
	t_env	*new;

	data->errnum = 0;
	i = 0;
	new = NULL;
	if (!data->cmd->cmd[1])
		return (if_without_arg(data->envp));

	// while (data->cmd->cmd[++i])///добавление элемента в конец списка
	// {

	// }

	ft_search_dups(data->envp, new, data);
	free_new(new);
	return (1);
}
