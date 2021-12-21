/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:19:18 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/21 20:07:52 by ogarthar         ###   ########.fr       */
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

void	execution(t_arg *data)
{
	int		fd;
	pid_t	child_pid = 0;

	if (data->cmd->cmd[0] && !(ft_strcmp(data->cmd->cmd[0], "exit")))
	{
		ft_exit_cmd(data);///
		exit(data->errnum);
	}
	ft_env_list_to_array(data->envp, data);
	if (!check_open(data))//проверяет и создает если нужно файлы для редир, обр-ка ошибок
	{
		data->num = ft_count_cmd(data->cmd);
		if (data->num == 1 && data->cmd->out)
			fd = dup_cmd(data->cmd, data);
		// if (data->num > 1)
		// {
		// 	ft_pipe(data);
		// }
		if (ft_check_builtin(data) != 1)
		{

			child_pid = fork();
			if (child_pid == 0)
			{
				child_process(&data);
			}
		}
		waitpid(child_pid, NULL, 0);
		if (data->num == 1 && data->cmd->out)
			redup_cmd(fd, data);
		// else if (data->num != 1 || data->cmd->cmd[0])
		// 	pipex(data);

	}
}

void free_cmd_redir(t_arg *data)
{
	t_command	*cmd_temp;
	t_redir		*redir_temp;

	while (data->cmd)
	{
		cmd_temp = data->cmd->next;
		free(data->cmd);
		data->cmd = cmd_temp;
	}
	while (data->redir)
	{
		redir_temp = data->redir->data_next;
		free(data->redir);
		data->redir = redir_temp;
	}
//	printf("free ok\n");
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

