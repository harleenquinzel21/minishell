/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 17:07:40 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/26 20:22:26 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cut_dots(t_env **pwd, t_env **oldpwd)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split((*pwd)->value, '.');
	(*pwd)->value = split[0];
	split = ft_split((*oldpwd)->value, '.');
	(*oldpwd)->value = split[0];
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

	/*	51	tmp1->value = NULL;//----------------OLDPWD*/
	/*	52	tmp1->value = ft_strdup(tmp->value);//--PWD*/
	/*	53	tmp->value = NULL;//--------------------PWD*/
	/*	54	tmp->value = ft_strdup(cd);//--------NEWPWD*/

void	env_after_cd(t_arg **data, char *cd)
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
		tmp1->value = NULL;
		tmp1->value = ft_strdup(tmp->value);
		tmp->value = NULL;
		tmp->value = ft_strdup(cd);
	}
	if ((*data)->cmd->cmd[1][0] == '.' && (*data)->cmd->cmd[1][1] == '.')
		ft_cut_dots(&tmp, &tmp1);
}

/*	70	cd = getcwd(NULL, 0);//----absolute path to current dir*/

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
		pwd = ft_strjoin(cd, "/");
		free(cd);
		cd = ft_strjoin(pwd, cmd->cmd[1]);
		free(pwd);
		return (cd);
	}
	while (envp && ft_strcmp(envp->key, "HOME"))
		envp = envp->next;
	if (envp)
	{
		pwd = ft_substr(cmd->cmd[1], 1, ft_strlen(cmd->cmd[1]) - 1);
		cd = ft_strjoin(envp->value, pwd);
		free(pwd);
	}
	return (cd);
}

void	ft_cd_error(t_arg *data, char *str)
{
	data->errnum = 2;
	write(2, "cd", 2);
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, " : No such file or directory\n", 29);
}

int	ft_cd(t_arg *data)
{
	char	*cd;

	cd = NULL;
	if (!data->cmd->cmd[1])
		data->cmd->cmd[1] = ft_strdup("~");
	cd = get_cd(data->cmd, data->envp, data);
	if (!cd)
	{
		write(2, "cd: HOME not set\n", 17);
		return (1);
	}
	if (access(cd, F_OK) == 0)
	{
		chdir(cd);
		env_after_cd(&data, cd);
	}
	else
		ft_cd_error(data, data->cmd->cmd[1]);
	free(cd);
	return (data->errnum);
}
