/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 20:02:15 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/03 21:03:14 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_init_structs(t_arg **data)
{
	(*data) = (t_arg *)malloc(sizeof (t_arg));
	if (!data)
		exit(EXIT_FAILURE);//обработать нормально через errno
	(*data)->cmd = (t_command *)malloc(sizeof (t_command));
	if (!(*data)->cmd)
		exit(EXIT_FAILURE);//обработать нормально через errno
	(*data)->redir = (t_redir *)malloc(sizeof (t_redir));
	if (!(*data)->redir)
		exit(EXIT_FAILURE);//обработать нормально через errno
	(*data)->cmd->cmd = ft_calloc(10, 10);

//*/*//*/*/*/*/*/*/*/**/*/*/*/*/**/*/*/*/*/*/
	(*data)->cmd->cmd[0] = "echo";
	// (*data)->cmd->cmd[1] = "-n";
	// (*data)->cmd->cmd[2] = "krgkrkg";
	(*data)->cmd->cmd[1] = "krgkr rrrr 12121 \'\\'kg";

}
