/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lvl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 19:17:06 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/27 16:36:31 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_shlvl_check(t_arg *data)
{
	t_env	*tmp;
	int		value;

	tmp = data->envp;
	value = 1;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "SHLVL") && !tmp->value[0])
		{
			free(tmp->separator);
			tmp->separator = ft_strdup("=", data);
			free(tmp->value);
			tmp->value = ft_strdup("1", data);
			return ;
		}
		else if (!ft_strcmp(tmp->key, "SHLVL") && tmp->value[0])
		{
			value += ft_atoi(tmp->value);
			free(tmp->value);
			tmp->value = ft_itoa(value, data);
			return ;
		}
		tmp = tmp->next;
	}
	env_add_new("SHLVL=1", &data->envp, data);
}
