/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 18:46:11 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/24 21:54:53 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_path(t_arg *data, char *cmd)
{
	t_env	*tmp;
	tmp = data->envp;

	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PATH"))
			return (0);
		tmp=tmp->next;
	}
	ft_print_error(2, NULL, cmd);
	return (1);
}

char	*find_path(char *cmd, char **envp, t_arg *data)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		ft_exit(12, "malloc", data);
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
	return (NULL);
}

static void	open_dup(int i, t_command *cmd, t_arg *data)
{
	int	file[2];

	file[0] = -2;
	if (cmd->in)
	{
		while (!cmd->in->target)
			cmd->in = cmd->in->next;
		file[0] = open(cmd->in->name, O_RDONLY);
	}
	if (file[0] == -1)
		ft_exit(errno, cmd->in->name, data);
	file[1] = -2;
	if (cmd->out)
	{
		while (!cmd->out->target)
				cmd->out = cmd->out->next;
		if (cmd->out && cmd->out->two)
			file[1] = open(cmd->out->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (cmd->out && !cmd->out->two)
			file[1] = open(cmd->out->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (file[1] == -1)
		ft_exit(errno, cmd->out->name, data);
	ft_dup2(i, file, cmd, data);
}

void	child_process(int i, t_arg *data)
{
	int			num;
	t_command	*cmd;
	char		*path;

	
	cmd = data->cmd;
	num = 0;
	while (num++ < i)
		cmd = cmd->next;
	if (!cmd->cmd || !cmd->cmd[0])
		exit(0);
	open_dup(i, cmd, data);
	if (cmd->built)
		ft_exit(run_built(cmd, data), NULL, data);

	// ft_putstr_fd("here!", 1);
	// if (!ft_check_path(data, cmd->cmd[0]))
	ft_check_path(data, cmd->cmd[0]);
		// return ;
	path = find_path(cmd->cmd[0], data->env, data);
	if (execve(path, cmd->cmd, data->env) == -1)
	{
		data->errnum = 127;
		ft_exit(data->errnum, cmd->cmd[0], data);
	}
}
