/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:28:40 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/24 21:35:33 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_arg *data)
{
	int	i;

	if (!data->cmd->cmd[1])
	{
		printf("\n");
		return (0);
	}
	//*/*/*/*/*/*/*/*/*/*/*/*/*/*/
	// if (!(ft_strcmp(data->cmd->cmd[1], "$?")))
	// {
	// 	free(data->cmd->cmd[1]);
	// 	data->cmd->cmd[1] = ft_strdup(ft_itoa(data->errnum));
	// }
	//*/*/*/*/*/*/*/*/*/*/*/*/*/
	i = 1;
	if (!(ft_strcmp(data->cmd->cmd[1], "-n")))
	{
		while (data->cmd->cmd[++i])
		{
			printf("%s", data->cmd->cmd[i]);
			if (data->cmd->cmd[i + 1] != NULL)
				printf(" ");
		}
		return (0);
	}
	i = 0;
	while (data->cmd->cmd[++i])
	{
		printf("%s", data->cmd->cmd[i]);
		if (data->cmd->cmd[i + 1] != NULL)
			printf(" ");
	}
	printf("\n");
	return (0);
}
