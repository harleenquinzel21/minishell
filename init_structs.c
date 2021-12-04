/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 20:02:15 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/04 17:48:32 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_init_structs(t_arg *data)
{
	data->cmd = malloc(sizeof(t_command));
	data->redir = NULL;
	data->envp = NULL;
	data->env = NULL;
	data->num = 0;
	data->fd = NULL;
	data->errnum = 0;
	
	
	// data = (t_arg *)malloc(sizeof (t_arg));
	// if (!data)
	// 	exit(EXIT_FAILURE);//обработать нормально через errno
	// (*data)->cmd = (t_command *)malloc(sizeof (t_command));
	// if (!(*data)->cmd)
	// 	exit(EXIT_FAILURE);//обработать нормально через errno
	// (*data)->redir = (t_redir *)malloc(sizeof (t_redir));
	// if (!(*data)->redir)
	// 	exit(EXIT_FAILURE);//обработать нормально через errno
	// (*data)->envp = (t_env *)malloc(sizeof (t_env));
	// if (!(*data)->envp)
//		exit(EXIT_FAILURE);//обработать нормально через errno
	//  (*data)->envp = NULL;

	// (*data)->cmd->cmd = ft_calloc(10, 10);

//*/*//*/*/*/*/*/*/*/**/*/*/*/*/**/*/*/*/*/*/
	// (*data)->cmd->cmd[0] = "env";
	// (*data)->envp->key = "USER";
	// (*data)->envp->separator = "=";
	// (*data)->envp->value = "ogarthar";
	// (*data)->envp->next = NULL;
	// printf("\n%s", (*data)->cmd->cmd[0]);///////
	// (*data)->cmd->cmd[1] = "-n";
	// // (*data)->cmd->cmd[2] = "krgkrkg";
	// // (*data)->cmd->cmd[1] = "str1 ";
	// (*data)->cmd->cmd[2] = "str 2 !";
	// (*data)->cmd->cmd[3] = "s t r 3 ";
}
