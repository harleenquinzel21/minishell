/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:19:18 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/04 17:59:23 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_check_builtin(t_arg *data)
{
	if (!(ft_strcmp(data->cmd->cmd[0], "pwd")))
		return (ft_pwd(data));
	else if (!(ft_strcmp(data->cmd->cmd[0], "echo")))
		return (ft_echo(data));
	else if (!(ft_strcmp(data->cmd->cmd[0], "env")))
		return (ft_env(data));
	// else if (!(ft_strcmp(data->cmd->cmd[0], "cd")))
	// 	return (ft_cd(data));
	// else if (!(ft_strcmp(data->cmd->cmd[0], "export")))
	// 	return (ft_export(data));

	// else if (!(ft_strcmp(data->cmd->cmd[0], "unset")))
	// 	return (ft_unset(data));
	else if (!(ft_strcmp(data->cmd->cmd[0], "exit")))
		ft_exit(0, NULL, data);///
	return (0);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (0);
}

void	execute(char **cmd, char **envp)
{
	if (execve(find_path(cmd[0], envp), cmd, envp) == -1)
	{
		write(1, "command not found: ", 19);
		write(1, &cmd[0], ft_strlen(cmd[0]));
	}
}

void	child_process(t_arg *data, char **envp)
{
	if (ft_check_builtin(data) != 1)
		execute(data->cmd->cmd, envp);
}



int	main(int ac, char **av, char **envp)
{
	t_arg	data;
	pid_t	child_pid;
	char	*line;

	(void)av;
	(void)ac;
	ft_init_structs(&data);
	

	if (ac != 1)
		ft_exit(1, NULL, NULL/*&data*/);

	while (1)
	{
		line = readline("\033[1;35m>>>\033[0;37m");
		
		if (line && *line)
			add_history(line);
		parser(envp, &data, line);
		child_pid = fork();
		if (child_pid == 0)
		{
			child_process(&data, envp);
		}
		waitpid(child_pid, NULL, 0);
		// return (0);
	}
	return (0);
}

