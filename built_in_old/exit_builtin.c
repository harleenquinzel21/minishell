/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:19:43 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/03 19:10:57 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../minishell.h"

void	ft_exit(int errnum, char *msg, t_arg *data)
{
	char	*errmsg;

	(void)data;///

	if (msg)
	{
		errmsg = strerror(errnum);
		write(2, msg, ft_strlen(msg));
		write(2, ": ", 2);
		write(2, errmsg, ft_strlen(errmsg));
		write(2, "\n", 1);
	}
	// ft_free(data);////
	exit(errnum);
}
