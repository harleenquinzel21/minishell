/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:19:18 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/01 22:07:21 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

void	execute(char *av, char **envp)
{
	char	**cmd;

	cmd = ft_split(av, ' ');
	if (execve(find_path(cmd[0], envp), cmd, envp) == -1)
	{
		write(1, "command not found: ", 19);
		write(1, &cmd[0], ft_strlen(cmd[0]));
	}
}

void	child_process(char **av, char **envp)
{
	execute(av[1], envp);
}

int	main(int ac, char **av, char **envp)
{
	// t_arg	main_struct;

	pid_t	child_pid;

	// (void)av;
	(void)ac;
	// (void)envp;

	// parser(ac, av, envp);
	// ft_init_structs(&main_struct);

	// if (ac != 1)
	// 	ft_exit(1, NULL, NULL/*&main_struct*/);
	while (1)
	{
		child_pid = fork();
		if (child_pid == 0)
			child_process(av, envp);
		waitpid(child_pid, NULL, 0);
		return (0);
	}



}

