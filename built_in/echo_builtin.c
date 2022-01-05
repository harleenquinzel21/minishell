/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:28:40 by ogarthar          #+#    #+#             */
/*   Updated: 2022/01/05 14:57:38 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_n(char *str)
{
	int	i;

	i = 1;
	if (!ft_strcmp(str, "-n"))
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_arg *data, t_command *cmd)
{
	int	i;

	i = 0;
	(void)data;
	if (!cmd->cmd[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	if (cmd->cmd[1][0] == '-' && check_n(cmd->cmd[1]))
		i = 1;
	while (cmd->cmd[++i])
	{
		ft_putstr_fd(cmd->cmd[i], 1);
		if (cmd->cmd[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (ft_strcmp(cmd->cmd[1], "-n"))
		ft_putstr_fd("\n", 1);
	return (0);
}
