/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 20:12:51 by ogarthar          #+#    #+#             */
/*   Updated: 2022/01/02 16:32:34 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	err_open(int errnum, char *text, t_arg *data)
{
	char	*errmsg;

	errmsg = strerror(errnum);
	write(2, text, ft_strlen(text));
	write(2, ": ", 2);
	write(2, errmsg, ft_strlen(errmsg));
	write(2, "\n", 1);
	data->errnum = errnum;
	return (1);
}

static int	open_file(t_redir *tmp, t_arg *data)
{
	int	fd;

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
