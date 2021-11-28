/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:55:52 by ogarthar          #+#    #+#             */
/*   Updated: 2021/11/28 14:30:35 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*key;
	char			*separator;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	char			*name;
	char			*limiter;
	int				cmd;
	int				in;
	int				two;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char				**cmd;
	t_redir				*in;
	t_redir				*out;
	struct s_command	*next;
}	t_command;

typedef struct s_arg
{
	t_command	*cmd;
	t_redir		*redir;
	t_env		envp;
	char		*env;
	int			num;
	int			**fd;
	int			errnum;
}	t_arg;

int	parser(int ac, char **av, char **envp);

int	ft_cd(char **args); //cd with only a relative or absolute path
// pwd with no options
// echo with option -n
//export with no options
// unset with no options
// env with no options or arguments

int ft_exit(char **args); //exit with no options




#endif
