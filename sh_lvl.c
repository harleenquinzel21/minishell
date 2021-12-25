/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lvl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 19:17:06 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/25 19:58:22 by ogarthar         ###   ########.fr       */
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
			tmp->separator = ft_strdup("=");
			free(tmp->value);
			tmp->value = ft_strdup("1");
			return ;
		}
		else if (!ft_strcmp(tmp->key, "SHLVL") && tmp->value[0])
		{
			value += ft_atoi(tmp->value);
			free(tmp->value);
			tmp->value = ft_itoa(value);
			return ;
		}
		tmp = tmp->next;
	}
	env_add_new("SHLVL=1", &data->envp);
}
