/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:05:39 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/09 20:41:17 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_cmd(t_command *cmd)
{
	int	res;

	res = 0;
	while (cmd)
	{
		res++;
		cmd = cmd->next;
	}
	return (res);
}

// void	ft_env_list_to_array(t_env *envp, char ***env, t_arg *arg)
// {
// 	int		len;

// 	len = ft_env_lstsize(envp);
// 	*env = malloc(sizeof(char *) * (len + 1));
// 	if (!*env)
// 		ft_exit(12, "malloc", arg);
// 	ft_make_array(envp, env, len, arg);
// }
