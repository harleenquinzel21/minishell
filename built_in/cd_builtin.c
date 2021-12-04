/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 17:07:40 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/04 19:08:41 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"


// ~~ Remplace le '~' par le HOME

// static int	replace_by_home_path(t_structs *s, char **path)
// {
// 	t_env	*elem;

// 	elem = find_env_var(s, "HOME");
// 	if (!elem || !elem->value)
// 		return (-1);
// 	else
// 		*(path) = ft_strdup(elem->value + 1);
// 	return (0);
// }

// char	*get_cd(t_cmd *cmd, t_env *env, t_arg *arg)
// {
// 	char	*cd;
// 	char	*pwd;

// 	cd = NULL;
// 	if (cmd->cmd[1][0] != '~')
// 	{
// 		cd = getcwd(NULL, 0);
// 		if (!cd)
// 			ft_exit(errno, "getcwd", arg);
// 		pwd = ft_strjoin_pars(cd, "/", arg);
// 		free(cd);
// 		cd = ft_strjoin_pars(pwd, cmd->cmd[1], arg);
// 		free(pwd);
// 		return (cd);
// 	}
// 	while (env && ft_strcmp(env->key, "HOME"))
// 		env = env->next;
// 	if (env)
// 	{
// 		pwd = ft_substr_pars(cmd->cmd[1], 1, \
// 				ft_strlen(cmd->cmd[1]) - 1, arg);
// 		cd = ft_strjoin_pars(env->value, pwd, arg);
// 		free(pwd);
// 	}
// 	return (cd);
// }

// int	ft_cd(t_cmd *cmd, t_env *env, t_arg *arg)
// {
// 	char	*cd;

// 	cd = NULL;
// 	if (!cmd->cmd[1])
// 	{
// 		while (env && ft_strcmp(env->key, "HOME"))
// 			env = env->next;
// 		if (env)
// 			cd = ft_strdup_pars(env->value, arg);
// 	}
// 	else
// 		cd = get_cd(cmd, env, arg);
// 	if (!cd)
// 	{
// 		write(2, "cd: HOME not set\n", 17);
// 		return (1);
// 	}
// 	chdir(cd);
// 	arg->errnum = errno;
// 	free(cd);
// 	return (arg->errnum);
// }
