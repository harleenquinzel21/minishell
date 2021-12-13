/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:19:18 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/14 00:06:00 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	ft_check_builtin(t_arg *data)
{
	// printf("start check builtin\n");
	// printf("-%s-\n", data->cmd->cmd[0]);
	if (data->cmd->cmd[0] == NULL)
		return (1);
	if (!(ft_strcmp(data->cmd->cmd[0], "pwd")))
		return (ft_pwd(data));
	else if (!(ft_strcmp(data->cmd->cmd[0], "echo")))
		return (ft_echo(data));
	else if (!(ft_strcmp(data->cmd->cmd[0], "env")))
		return (ft_env(data));
	else if (!(ft_strcmp(data->cmd->cmd[0], "cd")))
		return (ft_cd(data));
	else if (!(ft_strcmp(data->cmd->cmd[0], "export")))
		return (ft_export(data));
	else if (!(ft_strcmp(data->cmd->cmd[0], "unset")))
		return (ft_unset(data->cmd, data));
	// else if (!(ft_strcmp(data->cmd->cmd[0], "exit")))
	// {
	// 	ft_exit_cmd(data);///
	// 	exit(data->errnum);
	// }
	// printf("finish check builtin\n");
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_arg	*data;
	pid_t	child_pid;
	char	*line;

	(void)av;
	(void)ac;
	signal(SIGINT, &sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
	
	ft_init_structs(&data);
	if (ac != 1)
		ft_exit(1, NULL, NULL/*&data*/);
	parse_env(envp, data);
	ft_shlvl_check(&data);

	

	while (1)
	{

		go_readline(&line);

		if (line && *line)
			add_history(line);
		parser(data, line);
		data->num = ft_count_cmd(data->cmd);
		if (data->cmd->cmd[0] && !(ft_strcmp(data->cmd->cmd[0], "exit")))
		{
			ft_exit_cmd(data);///
			exit(data->errnum);
		}
		if (ft_check_builtin(data) != 1)
		{
			
			child_pid = fork();
			if (child_pid == 0)
			{
				child_process(&data);
			}
			
		}

		waitpid(child_pid, NULL, 0);
	}
	return (0);
}

