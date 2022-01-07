/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 13:36:49 by ogarthar          #+#    #+#             */
/*   Updated: 2022/01/07 17:44:35 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_after_cd(t_arg **data)
{
	t_env	*tmp;
	t_env	*tmp1;

	tmp = (*data)->envp;
	tmp1 = (*data)->envp;
	while (tmp && ft_strcmp(tmp->key, "PWD"))
		tmp = tmp->next;
	while (tmp1 && ft_strcmp(tmp1->key, "OLDPWD"))
		tmp1 = tmp1->next;
	if (tmp && tmp1)
	{
		free(tmp1->value);
		tmp1->value = ft_strdup(tmp->value, *data);
		free(tmp->value);
		tmp->value = getcwd(NULL, 0);
		if (!tmp->value)
			ft_exit(errno, "getcwd", *data);
	}
}

/*	47	cd = getcwd(NULL, 0);//----absolute path to current dir*/

char	*get_cd(t_command *cmd, t_env *envp, t_arg *data)
{
	char	*cd;
	char	*pwd;

	cd = NULL;
	if (cmd->cmd[1][0] != '~')
	{
		cd = getcwd(NULL, 0);
		if (!cd)
			ft_exit(errno, "getcwd", data);
		pwd = ft_strjoin(cd, "/", data);
		free(cd);
		cd = ft_strjoin(pwd, cmd->cmd[1], data);
		free(pwd);
		return (cd);
	}
	while (envp && ft_strcmp(envp->key, "HOME"))
		envp = envp->next;
	if (envp)
	{
		pwd = ft_substr(cmd->cmd[1], 1, ft_strlen(cmd->cmd[1]) - 1, data);
		cd = ft_strjoin(envp->value, pwd, data);
		free(pwd);
	}
	return (cd);
}

void	ft_cd_error(t_arg *data, char *str)
{
	data->errnum = 1;
	write(2, "cd", 2);
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, " : No such file or directory\n", 29);
}

int	ft_cd(t_arg *data, t_command *cmd)
{
	char	*cd;

	cd = NULL;
	if (!cmd->cmd[1])
		cmd->cmd[1] = ft_strdup("~", data);
	cd = get_cd(cmd, data->envp, data);
	if (!cd)
	{
		write(2, "cd: HOME not set\n", 17);
		return (1);
	}
	if (access(cd, F_OK) == 0 && data->num == 1)
	{
		chdir(cd);
		env_after_cd(&data);
	}
	else
		ft_cd_error(data, cmd->cmd[1]);
	free(cd);
	return (data->errnum);
}
