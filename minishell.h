/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:55:52 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/26 15:04:53 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
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
	int				target;
	int				two;
	int				in;
	struct s_redir	*next;
	struct s_redir	*data_next;
}	t_redir;

typedef struct s_cmd
{
	char			**cmd;
	t_redir			*in;
	t_redir			*out;
	int				built;
	struct s_cmd	*next;
}	t_command;

typedef struct s_arg
{
	t_command	*cmd;
	t_redir		*redir;
	t_env		*envp;
	char		**env;
	int			num;
	int			num_cmd;
	int			**fd;
	int			errnum;
}	t_arg;

int g_errnum;

void	ft_print_all(t_arg *data);

/*./parser*/
void	rl_replace_line(const char *str, int num);
void	go_readline(char **line);

int	unclosed_quotes(char *line);
int	unclosed_double_quotes(char *line);
int	wrong_semicolon(char *line);
int	double_semicolon(char *line);





int		parser(t_arg *data, char *line);
char	*parse_line(char *line_const, t_arg *data, t_command *cmd);
int		check_syntax(char *line, t_arg *data);
char	*single_quotes(char *line, int *i);
char	*double_quotes(char *line, int *i, t_env *envp);

char	*parse_redirects(char *line, int *i, t_command *cmd, t_arg *data);
t_redir	*new_redir(char *line, int *i, t_arg *data);

void	parse_env(char **envp, t_arg *data);
t_env	*env_create_new(char *key, char *sep, char *value);
void	env_add_new(char *env_line, t_env **first);
char	*env_replace(char *line, int *i, t_env *envp);
char	*exit_code_replace(char *line, t_arg *data);


/*signals*/
void	sig_handler(int sig_num);
void	sig_int_handler(int sig_num);
void	sig_handler_child(int sig_num);
void	sig_handler_parent(int sig_num);

/*utils*/
int		ft_count_cmd(t_command *cmd);
int		ft_count_envp(t_env *envp);
void	ft_env_list_to_array(t_env *envp, t_arg *data);
void	ft_make_array(t_env *envp, char **env, int len, t_arg *data);
void	ft_print_error(int errnum, char *str, char *cmd_name);

/*check_open.c*/
int	check_open(t_arg *data);

/*child.c*/
void	child_process(int i, t_arg *data);
void	execute(char **cmd, char **env, t_arg *data);
char	*find_path(char *cmd, char **envp, t_arg *data);
int		ft_check_path(t_arg *data, char *cmd);

/*redirects.c*/
int		dup_cmd(t_command *cmd, t_arg *data);
void	redup_cmd(int fd, t_arg *data);
/*pipe.c*/
void	ft_pipe(t_arg *data);
/*pipex.c*/
void	pipex(t_arg *data);
void	ft_dup2(int i, int *file, t_command *cmd, t_arg *data);

/*./built_in*/
int		ft_cd(t_arg *data); //cd with only a relative or absolute path
int		ft_pwd(t_arg *data);// pwd with no options
int		ft_env(t_arg *data);// env with no options or arguments
int		ft_echo(t_arg *data);// echo with option -n
int		ft_unset(t_command *cmd, t_arg *data);// unset with no options
int		ft_export(t_arg *data);//export with no options
int		ft_add_new(char *str, t_arg *data);
int		ft_export_join(char *str, t_env *envp);
void	ft_export_unset_error(t_arg *data, char *str, char *namecmd);
void	ft_cd_error(t_arg *data, char *str);
int		ft_exit_cmd(t_arg *data);
int		check_exit(t_arg *data);
int		ft_exit(int errnum, char *msg, t_arg *data); //exit with no options
void	free_cmd_redir(t_arg *data);
int		ft_last_err(t_arg *data);

void	ft_shlvl_check(t_arg *data);
void	ft_init_structs(t_arg **data);
int		run_built(t_command *cmd, t_arg *data);
void	heredoc(char *name, char *limiter, t_arg *data);

#endif
