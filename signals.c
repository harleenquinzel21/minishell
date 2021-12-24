/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:51:22 by fbeatris          #+#    #+#             */
/*   Updated: 2021/12/24 19:51:25 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_readline(char **line)
{
	rl_on_new_line();
	*line = readline(">>> ");
	if (*line && **line)
		add_history(*line);
	else if (*line == NULL)
	{
		printf("\033[1A>>> exit\n");
		exit(0);
	}
}

void	sig_handler(int sig_num) // dosn't work :(
{
		if (sig_num == SIGINT)
		{
			rl_on_new_line();
			rl_redisplay();
			write(1, "  \b\b!!!\n", 8);
			rl_on_new_line();
			rl_replace_line("", 1);
			rl_redisplay();
			exit(2);
		}
		else if (sig_num == SIGQUIT)
		{
			write(2, "Quit: 3!!!\n", 11);
			exit(3);
		}
}

void	sig_int_handler(int sig_num)
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
}
