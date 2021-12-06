/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:17:44 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/05 14:26:12 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	ft_env(t_arg *data)
{
	t_env	*tmp;

	if (!(data->envp))
		return (0);
	tmp = data->envp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->separator, "="))
		printf("%s%s%s\n", tmp->key, tmp->separator, tmp->value);
		tmp = tmp->next;
	}
	return (1);
}
