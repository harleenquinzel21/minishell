/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 18:46:11 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/13 20:54:28 by fbeatris         ###   ########.fr       */
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
			return (1);
		tmp=tmp->next;
	}
	ft_print_error(2, NULL, cmd);
	return (0);
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

void	execute(char **cmd, char **env, t_arg *data)
{

	if (!ft_check_path(data, *cmd))
		return ;
	if (execve(find_path(cmd[0], env, data), cmd, env) == -1)
	{
		write(2, "minishell: command not found: ", 30);
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, "\n", 1);
	}

}



void	child_process(t_arg **data)
{
	
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
	ft_env_list_to_array((*data)->envp, *data);
		execute((*data)->cmd->cmd, (*data)->env, *data);

}
