/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:06:28 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/23 21:02:38 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_arg *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_exit(errno, "getcwd", data);
	printf("%s\n", pwd);
	free(pwd);
	data->errnum = 0;
	return (0);
}

// int	ft_last_err(t_arg *data)
// {
// 	// char	*errmsg;

// 	if (!data->errnum)
// 		ft_putstr_fd("0: command not found\n", 2);
// 	else
// 	{
// 		// errmsg = strerror(data->errnum);
// 		ft_putnbr_fd(data->errnum, 2);
// 		write(2, ": ", 2);
// 		ft_putstr_fd("0: command not found\n", 2);
// 		// write(2, errmsg, ft_strlen(errmsg));
// 		write(2, "\n", 1);
// 	}
// 	return (0);
// }
