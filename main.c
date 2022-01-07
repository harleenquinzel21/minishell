/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 20:04:11 by ogarthar          #+#    #+#             */
/*   Updated: 2022/01/07 20:34:53 by fbeatris         ###   ########.fr       */
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

int	run_built(t_command *cmd, t_arg *data)
{
	if (cmd->built == 1)
		return (ft_echo(data, cmd));
	if (cmd->built == 2)
		return (ft_cd(data, cmd));
	if (cmd->built == 3)
		return (ft_pwd(data));
	if (cmd->built == 4)
		return (ft_export(data, cmd));
	if (cmd->built == 5)
		return (ft_unset(cmd, data));
	if (cmd->built == 6)
		return (ft_env(data, cmd));
	if (cmd->built == 7)
		return (ft_exit_cmd(data, cmd));
	return (0);
}

void	execution(t_arg *data)
{
	int	fd;

	fd = 0;
	set_built(data->cmd);
	ft_env_list_to_array(data->envp, data);
	if (!check_open(data))
	{
		data->num = ft_count_cmd(data->cmd);
		if (data->num == 0)
			return ;
		if (data->num > 1)
		{
			ft_pipe(data);
		}
		if (data->num == 1 && data->cmd->built)
		{
			fd = dup_cmd(data->cmd, data);
			data->errnum = run_built(data->cmd, data);
			redup_cmd(fd, data);
		}
		else if (data->num != 1 || data->cmd->cmd[0])
			pipex(data);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_arg	*data;
	char	*line;

	(void)av;
	ft_init_structs(&data);
	if (ac != 1)
		ft_exit(1, NULL, data);
	parse_env(envp, data);
	ft_shlvl_check(data);
	while (1)
	{
		go_readline(&line, data);
		if (parser(data, line) == 0)
		{
			execution(data);
			free_structs(data);
		}
	}
	return (0);
}
