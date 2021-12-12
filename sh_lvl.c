/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lvl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 19:17:06 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/12 19:34:33 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_if_shlvl(t_env *tmp)
{
	int	value;

	value = 1;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "SHLVL") && !tmp->value[0])
		{
			free(tmp->separator);
			tmp->separator = ft_strdup("=");
			free(tmp->value);
			tmp->value = ft_strdup("1");
			return (1);
		}
		else if (!ft_strcmp(tmp->key, "SHLVL") && tmp->value[0])
		{
			value += ft_atoi(tmp->value);
			free(tmp->value);
			tmp->value = ft_itoa(value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_shlvl_check(t_arg **data)
{
	t_env	*tmp;
	char	*line;

	tmp = (*data)->envp;
	if (!ft_if_shlvl(tmp))
	{
		// tmp = malloc(sizeof(t_env));
		// if (!tmp)
		// 	ft_exit(12, "malloc", data);
		line = ft_strdup("SHLVL=1");
		env_add_new(line, &tmp);
		free(line);
	}
}
