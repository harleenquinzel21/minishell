/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:17:44 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/09 16:51:32 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_arg *data)
{
	t_env	*tmp;

	if (!(data->envp))
		return (0);
	tmp = data->envp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->separator, "="))
		{
			ft_putstr_fd(tmp->key, 1);
			ft_putstr_fd(tmp->separator, 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\n", 1);
			tmp = tmp->next;
		}
	}
	return (1);
}
