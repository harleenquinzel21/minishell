/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:28:40 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/03 20:57:17 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	ft_echo(t_arg *data)
{
	int	i;

	i = 2;
	if (!(ft_strcmp(data->cmd->cmd[1], "-n")))
	{
		while (data->cmd->cmd[i])
			printf("%s", data->cmd->cmd[i++]);
	}
	else
	{
		i = 1;
		while (data->cmd->cmd[i])
			printf("%s", data->cmd->cmd[i++]);
		printf("\n");
	}
	return (1);
}
