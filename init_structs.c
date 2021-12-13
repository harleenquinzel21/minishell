/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 20:02:15 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/13 23:23:49 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_init_structs(t_arg **data)
{
	// (*data)->cmd = malloc(sizeof(t_command));
	// (*data)->redir = NULL;
	// (*data)->envp = NULL;
	// (*data)->env = NULL;
	// (*data)->num = 0;
	// (*data)->fd = NULL;
	// (*data)->errnum = 0;


	(*data) = (t_arg *)malloc(sizeof (t_arg));
	if (!(*data))
	{
		write(1, "1", 1);
		sleep(3);
	}
		// exit(EXIT_FAILURE);//обработать нормально через errno

	(*data)->cmd = (t_command *)malloc(sizeof (t_command));
	if (!(*data)->cmd)
	{
		write(1, "2", 1);
		sleep(3);
	}
		// exit(EXIT_FAILURE);//обработать нормально через errno

	(*data)->cmd->in = NULL;
	(*data)->cmd->out = NULL;


/*
	(*data)->cmd->in = (t_redir *)malloc(sizeof (t_redir));
	if (!(*data)->cmd->in)
	{
		// sleep(3);
		write(1, "2", 1);
		sleep(3);
		// return;
	}
	(*data)->cmd->out = (t_redir *)malloc(sizeof (t_redir));
	if (!(*data)->cmd->out)
	{
		// sleep(3);
		write(1, "2", 1);
		sleep(3);
		// return;
	}
*/
	(*data)->redir = (t_redir *)malloc(sizeof (t_redir));
	if (!(*data)->redir)
	{
		write(1, "2", 1);
		sleep(3);
	}
		// exit(EXIT_FAILURE);//обработать нормально через errno

	(*data)->envp = NULL;


	// (*data)->cmd->cmd = ft_calloc(10, 10);

//*/*//*/*/*/*/*/*/*/**/*/*/*/*/**/*/*/*/*/*/
	// (*data)->cmd->cmd[0] = "env";
	// (*data)->cmd->cmd[1] = "";
	// (*data)->cmd->cmd[1] = "";
	// (*data)->cmd->cmd[1] = "builtin";

	// if(!((*data)->envp->next = (t_env *)malloc(sizeof (t_env))))
	// {
	// 	// sleep(3);
	// 	write(1, "2", 1);
	// 	sleep(3);
	// 	// return;
	// }
	// if (!((*data)->envp->next->next = (t_env *)malloc(sizeof (t_env))))
	// {
	// 	// sleep(3);
	// 	write(1, "2", 1);
	// 	sleep(3);
	// 	// return;
	// }

	// (*data)->envp->key = "HOME";
	// (*data)->envp->next->key = "PWD";
	// (*data)->envp->next->next->key = "OLDPWD";
	// (*data)->envp->separator = "=";
	// (*data)->envp->next->separator = "=";
	// (*data)->envp->next->next->separator = "=";
	// (*data)->envp->value = "/Users/ogarthar";
	// (*data)->envp->next->value = "/Users/ogarthar/minishell";
	// (*data)->envp->next->next->value = "/Users/ogarthar";


	// ft_putstr_fd("OLDPWD: ", 1);
	// ft_putstr_fd((*data)->envp->next->next->value, 1);
	// ft_putstr_fd("PWD: ", 1);
	// ft_putstr_fd((*data)->envp->next->value, 1);

	// printf("\n%s", (*data)->cmd->cmd[0]);///////
	// (*data)->cmd->cmd[1] = "-n";
	// // (*data)->cmd->cmd[2] = "krgkrkg";
	// // (*data)->cmd->cmd[1] = "str1 ";
	// (*data)->cmd->cmd[2] = "str 2 !";
	// (*data)->cmd->cmd[3] = "s t r 3 ";
}
