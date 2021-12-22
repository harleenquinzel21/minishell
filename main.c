/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:19:18 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/22 15:44:42 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_built(t_command *cmd)
{
	while (cmd)
	{
		if (cmd->cmd[0])
		{
			if (!ft_strcmp(cmd->cmd[0], "echo"))
				cmd->built = 1;
			else if (!ft_strcmp(cmd->cmd[0], "cd"))
				cmd->built = 2;
			else if (!ft_strcmp(cmd->cmd[0], "pwd"))
				cmd->built = 3;
			else if (!ft_strcmp(cmd->cmd[0], "export"))
				cmd->built = 4;
			else if (!ft_strcmp(cmd->cmd[0], "unset"))
				cmd->built = 5;
			else if (!ft_strcmp(cmd->cmd[0], "env"))
				cmd->built = 6;
			else if (!ft_strcmp(cmd->cmd[0], "exit"))
				cmd->built = 7;
		}
		cmd = cmd->next;
	}
}

// int	ft_check_builtin(t_arg *data)
// {
// 	// printf("start check builtin\n");
// 	// printf("-%s-\n", data->cmd->cmd[0]);
// 	if (data->cmd->cmd[0] == NULL)
// 		return (1);
// 	if (!(ft_strcmp(data->cmd->cmd[0], "pwd")))
// 		return (ft_pwd(data));
// 	else if (!(ft_strcmp(data->cmd->cmd[0], "echo")))
// 		return (ft_echo(data));
// 	else if (!(ft_strcmp(data->cmd->cmd[0], "env")))
// 		return (ft_env(data));
// 	else if (!(ft_strcmp(data->cmd->cmd[0], "cd")))
// 		return (ft_cd(data));
// 	else if (!(ft_strcmp(data->cmd->cmd[0], "export")))
// 		return (ft_export(data));
// 	else if (!(ft_strcmp(data->cmd->cmd[0], "unset")))
// 		return (ft_unset(data->cmd, data));
// 	// else if (!(ft_strcmp(data->cmd->cmd[0], "exit")))
// 	// {
// 	// 	ft_exit_cmd(data);///
// 	// 	exit(data->errnum);
// 	// }
// 	// printf("finish check builtin\n");
// 	return (0);
// }

int	run_built(t_command *cmd, t_arg *data)
{
	if (cmd->built == 1)
		return (ft_echo(data));
	if (cmd->built == 2)
		return (ft_cd(data));
	if (cmd->built == 3)
		return (ft_pwd(data));
	if (cmd->built == 4)
		return (ft_export(data));
	if (cmd->built == 5)
		return (ft_unset(data->cmd, data));
	if (cmd->built == 6)
		return (ft_env(data));
	if (cmd->built == 7)
		return (ft_exit_cmd(data));
	return (0);
}

void	execution(t_arg *data)
{
	int		fd = 0;
	// pid_t	child_pid = 0;

	// if (data->cmd->cmd[0] && !(ft_strcmp(data->cmd->cmd[0], "exit")))
	// {
	// 	ft_exit_cmd(data);///
	// 	exit(data->errnum);
	// }
	set_built(data->cmd);
	ft_env_list_to_array(data->envp, data);
	if (!check_open(data))//проверяет и создает если нужно файлы для редир, обр-ка ошибок
	{
		data->num = ft_count_cmd(data->cmd);
		if (data->num == 1 && data->cmd->built)
		{
			fd = dup_cmd(data->cmd, data);
			data->errnum = run_built(data->cmd, data);
			redup_cmd(fd, data);
		}
		if (data->num > 1)
		{
			ft_pipe(data);
		}
		if (data->num != 1 || data->cmd->cmd[0])
			pipex(data);

	}
}

int	main(int ac, char **av, char **envp)
{
	t_arg	*data;
	char	*line;
	(void)av;

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

		ft_print_all(data);//

		execution(data);
		free_cmd_redir(data);
	}

	return (0);
}

