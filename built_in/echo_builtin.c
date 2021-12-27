/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:28:40 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/27 18:23:13 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_arg *data)
{
	int	i;

	i = 0;
	if (!data->cmd->cmd[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	if (!(ft_strcmp(data->cmd->cmd[1], "-n")))
		i = 1;
	while (data->cmd->cmd[++i])
	{
		ft_putstr_fd(data->cmd->cmd[i], 1);
		if (data->cmd->cmd[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (ft_strcmp(data->cmd->cmd[1], "-n"))
		ft_putstr_fd("\n", 1);
	return (0);
}
