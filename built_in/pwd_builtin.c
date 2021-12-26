/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:06:28 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/26 19:23:01 by ogarthar         ###   ########.fr       */
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
