/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:03:40 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/22 15:32:51 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(t_arg *data)
{
	int	i;

	// ft_putstr_fd("here\n", 1);

	data->fd = malloc((data->num - 1) * sizeof(int *));
	if (!data->fd)
		ft_exit(errno, "malloc", data);
	i = -1;
	while (++i < data->num - 1)
	{
		data->fd[i] = malloc(2 * sizeof(int));
		if (!data->fd[i])
			ft_exit(errno, "malloc", data);
		if (pipe(data->fd[i]) == -1)
		{
			data->errnum = errno;
			while (i--)
			{
				close(data->fd[i][0]);
				close(data->fd[i][1]);
			}
			ft_exit(data->errnum, "pipe", data);
		}
	}
}
