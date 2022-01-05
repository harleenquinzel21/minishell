/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:17:44 by ogarthar          #+#    #+#             */
/*   Updated: 2022/01/05 19:46:10 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_arg_export(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]))
		return (1);
	while (str[i] && (str[i] == '_' || ft_isalnum(str[i])))
		i++;
	if (str[i] == '+' && str[i + 1] != '=')
	{
		// ft_export_unset_error(data, str, "export");
		return (1);
	}
	return (0);
}

void	ft_env_error(t_arg *data, char *str)
{
	data->errnum = 127;
	write(2, "env", 3);
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, " : No such file or directory\n", 29);
}

int	ft_env(t_arg *data, t_command *cmd)
{
	t_env	*tmp;

	if (!(data->envp))
		return (1);
	if (cmd->cmd[1])
	{
		ft_env_error(data, cmd->cmd[1]);
		return (data->errnum);
	}
	tmp = data->envp;
	while (tmp)
	{
		if (tmp->separator && !ft_strcmp(tmp->separator, "="))
		{
			ft_putstr_fd(tmp->key, 1);
			ft_putstr_fd(tmp->separator, 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
