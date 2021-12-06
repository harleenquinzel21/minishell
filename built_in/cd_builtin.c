/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 17:07:40 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/06 19:27:55 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"				//to do: "..", "../../.."

void	ft_cut_dots(t_env **pwd, t_env **oldpwd)
{
	int	i;
	i = 0;

	char	**split;
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

/*/*//*/*////*/*/*/*/*///*/*//*/*////*/*/*/*/*//
	ft_putstr_fd("OLDPWD: ", 1);
	ft_putstr_fd(tmp1->value, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("PWD: ", 1);
	ft_putstr_fd(tmp->value, 1);
	ft_putstr_fd("\n", 1);
/*/*//*/*////*/*/*/*/*///*/*//*/*////*/*/*/*/*//

	if (tmp && tmp1)
	{
		tmp1->value = NULL;//OLDPWD
		tmp1->value = ft_strdup(tmp->value);//PWD
		tmp->value = NULL;//PWD
		tmp->value = ft_strdup(cd);//NEWPWD
	}
	if ((*data)->cmd->cmd[1][0] == '.' && (*data)->cmd->cmd[1][1] == '.')
		ft_cut_dots(&tmp, &tmp1);

/*/*//*/*////*/*/*/*/*///*/*//*/*////*/*/*/*/*//
	ft_putstr_fd("OLDPWD: ", 1);
	ft_putstr_fd(tmp1->value, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("PWD: ", 1);
	ft_putstr_fd(tmp->value, 1);
	ft_putstr_fd("\n", 1);
/*/*//*/*////*/*/*/*/*///*/*//*/*////*/*/*/*/*//
}

char	*get_cd(t_command *cmd, t_env *envp, t_arg *data)
{
	char	*cd;
	char	*pwd;

	cd = NULL;
	if (cmd->cmd[1][0] != '~')
	{
		cd = getcwd(NULL, 0);//абсолютный путь к текущему каталогу
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

int	ft_cd(t_arg *data)
{
	char	*cd;
	t_env	*tmp;

	tmp = data->envp;
	cd = NULL;
	if (!data->cmd->cmd[1])
		data->cmd->cmd[1] = "~";
		// if (!data->cmd->cmd[1])
		// {
		// 	while (tmp && ft_strcmp(tmp->key, "HOME"))
		// 		tmp = tmp->next;
		// 	if (tmp)
		// 		cd = ft_strdup(tmp->value);
		// }
		// else
		// 	cd = get_cd(data->cmd, data->envp, data);
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
	data->errnum = errno;
	free(cd);
	return (1);
}
