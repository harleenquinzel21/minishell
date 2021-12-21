#include "minishell.h"

void	ft_print_all(t_arg *data)
{
	t_command	*cmd;
	t_redir		*redir;
	int			i;
	int			j = 1;

	if (!data->cmd->cmd[0])
		return ;
	ft_putstr_fd("\033[1;36m\n		data->cmd\n", 1);
	cmd = data->cmd;
	while (cmd)
	{
		i = -1;
		while (cmd->cmd[++i])
		{
			ft_putnbr_fd(j, 1);
			ft_putstr_fd(". cmd->cmd[", 1);
			ft_putnbr_fd(i, 1);
			ft_putstr_fd("] = ", 1);
			ft_putstr_fd(cmd->cmd[i], 1);
			ft_putstr_fd("\n", 1);
		}
		cmd = cmd->next;
		j++;
	}
	ft_putstr_fd("\n\033[0;37m", 1);
	if (!data->redir)
		return ;
	redir = data->redir;
	j = 1;
	ft_putstr_fd("\033[1;36m\n		data->redir\n", 1);
	while (redir)
	{
		ft_putnbr_fd(j, 1);
		ft_putstr_fd(". cmd:", 1);
		ft_putnbr_fd(redir->cmd, 1);
		ft_putstr_fd(" ", 1);
		if (redir->two && !redir->in)
			ft_putstr_fd(">> ", 1);
		else if (!redir->two && !redir->in)
			ft_putstr_fd("> ", 1);
		else if (!redir->two && redir->in)
			ft_putstr_fd("< ", 1);
		else if (redir->limiter && redir->in)
		{
			ft_putstr_fd("<< ", 1);
			ft_putstr_fd("limiter: ", 1);
			ft_putstr_fd(redir->limiter, 1);
		}
		if (redir->name)
			ft_putstr_fd(redir->name, 1);
		if (redir->target)
			ft_putstr_fd(" is target ", 1);
		ft_putstr_fd(" ", 1);
		ft_putstr_fd("\n", 1);
		redir = redir->data_next;
		j++;
	}
	ft_putstr_fd("\n\033[0;37m", 1);
	// if (!data->cmd->in && !data->cmd->out)
	// 	return ;

}
