/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 20:26:15 by fbeatris          #+#    #+#             */
/*   Updated: 2022/01/08 16:28:19 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sort_env_compare(t_env *first, t_env *second)
{
	int	i;

	i = 0;
	while (first->key[i])
	{
		if (first->key[i] > second->key[i])
			return (1);
		else if (first->key[i] < second->key[i])
			return (-1);
		else
			i++;
	}
	return (0);
}

t_env	*sort_env_find_first(t_arg *data)
{
	t_env	*first;
	t_env	*temp;

	first = data->envp;
	temp = data->envp;
	while (temp)
	{
		if (sort_env_compare(temp, first) <= 0)
			first = temp;
		temp = temp->next;
	}
	return (first);
}

t_env	*sort_env_find_last(t_arg *data)
{
	t_env	*first;
	t_env	*temp;

	first = data->envp;
	temp = data->envp;
	while (temp)
	{
		if (sort_env_compare(temp, first) > 0)
			first = temp;
		temp = temp->next;
	}
	return (first);
}

t_env	*sort_env_find_next(t_arg *data, t_env *current)
{
	t_env	*temp;
	t_env	*new;

	temp = data->envp;
	new = sort_env_find_last(data);
	while (temp)
	{
		if (sort_env_compare(temp, new) <= 0 && \
			sort_env_compare(temp, current) > 0 && \
			ft_strcmp(temp->key, "_"))
			new = temp;
		temp = temp->next;
	}
	return (new);
}

void	sort_env(t_arg *data)
{
	t_env	*current;
	t_env	*new;
	t_env	*temp;
	int		i;

	i = 0;
	temp = data->envp;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	current = sort_env_find_first(data);
	data->envp_alpha = current;
	while (i > 0)
	{
		new = sort_env_find_next(data, current);
		current->alpha_next = new;
		current = new;
		i--;
	}
	current->alpha_next = NULL;
}
