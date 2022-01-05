/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 20:12:51 by ogarthar          #+#    #+#             */
/*   Updated: 2022/01/05 20:44:55 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	err_open(int errnum, char *text, t_arg *data)
{
	char	*errmsg;
	if (errnum == 1)
	{
		ft_putstr_fd(text, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
	}
	else
	{
		errmsg = strerror(errnum);
		write(2, text, ft_strlen(text));
		write(2, ": ", 2);
		write(2, errmsg, ft_strlen(errmsg));
		write(2, "\n", 1);
	}
	data->errnum = errnum;
	return (1);
}

int	ambiguous_redirect(t_redir *tmp, t_arg *data)
{
	t_env	*env;

	if (tmp->name[0] != '$')
		return (0);
	env = data->envp;
	while (env)
	{
		if (!(ft_strcmp(env->key, ft_substr(tmp->name, \
		1, ft_strlen(tmp->name), data))))
		{
			if (env->value)
			{
				free (tmp->name);
				tmp->name = ft_strdup(env->value, data);
				return (0);
			}
		}
		env = env->next;
	}
	return (1);
}

static int	open_file(t_redir *tmp, t_arg *data)
{
	int	fd;

	// if (tmp->name[0] == '$')//
	if (ambiguous_redirect(tmp, data))
		return (err_open(1, tmp->name, data));//print ambiguous redirect
	if (!tmp->in && tmp->two) //// >>
	{
		fd = open(tmp->name, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (err_open(errno, tmp->name, data));
	}
	else if (!tmp->in && !tmp->two)
	{
		fd = open(tmp->name, O_RDWR | O_CREAT | O_TRUNC, 0644); ////>
		if (fd == -1)
			return (err_open(errno, tmp->name, data));
	}
	else
	{
		fd = open(tmp->name, O_RDWR); //<
		if (fd == -1)
			return (err_open(errno, tmp->name, data));
	}
	close(fd);
	return (0);
}

int	check_open(t_arg *data)
{
	t_redir	*tmp;

	tmp = data->redir;
	while (tmp)
	{
		if (!tmp->in || !tmp->two)
		{
			if (open_file(tmp, data))
				return (1);
		}
		else
			heredoc(tmp->name, tmp->limiter, data);
		tmp = tmp->data_next;
	}
	return (0);
}
