/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:19:43 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/01 21:00:01 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "minishell.h"

void	ft_exit(int errnum, char *msg, t_arg *main_struct)
{
	char	*errmsg;

	(void)main_struct;///

	if (msg)
	{
		errmsg = strerror(errnum);
		write(2, msg, ft_strlen(msg));
		write(2, ": ", 2);
		write(2, errmsg, ft_strlen(errmsg));
		write(2, "\n", 1);
	}
	// free_arg(main_struct);////
	exit(errnum);
}
