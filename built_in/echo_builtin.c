/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:28:40 by ogarthar          #+#    #+#             */
/*   Updated: 2022/01/02 19:58:28 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_n(char *str)
{
	int i = 1;

	if (!ft_strcmp(str, "-n"))
		return (0);
	while (str[i])
	{
		if (str[0] == '-')
		{
			if (str[i] != 'n')
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_echo(t_arg *data)
{
	int	i;

	i = 0;
	if (!data->cmd->cmd[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	if (!check_n(data->cmd->cmd[1]))
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
