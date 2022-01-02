/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:51:22 by fbeatris          #+#    #+#             */
/*   Updated: 2022/01/02 14:54:06 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_readline(char **line, t_arg *data)
{
	// int a = 0;

	signal(SIGINT, &sig_handler_parent);
	signal(SIGQUIT, &sig_handler_parent);

	// a = rl_on_new_line();
	rl_on_new_line();
	*line = readline(">>> ");

	if (*line && **line)
		add_history(*line);
	else if (*line == NULL)
	{
		printf("\033[1A>>> exit\n");
		ft_exit(data->errnum, NULL, data);
	}
	// if (ft_strcmp(*line, "") == 0)
	// 	data->errnum = 0;
	// printf("errnum: %d\nrl: %d\n", data->errnum, a);////////////////
}

void	sig_handler_child(int sig_num)
{
	if (sig_num == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
	}
	else if (sig_num == SIGQUIT)
	{
		write(2, "Quit: 3\n", 8);
	}
}

void	sig_handler_parent(int sig_num)
{
	if (sig_num == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b\n", 5);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else if (sig_num == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		write(1, "  \b\b", 4);
	}
}
