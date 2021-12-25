/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:09:43 by fbeatris          #+#    #+#             */
/*   Updated: 2021/12/25 19:03:34 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*new_command(void)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	new->in = NULL;
	new->out = NULL;
	new->next = NULL;
	new->cmd = NULL;
	new->built = 0;
	return (new);
}

char	*parse_line(char *line_const, t_arg *data, t_command *cmd)
{
	char	*line;
	char	*one_cmd;
	int		i;

	i = 0;
	line = ft_strdup(line_const);
	while (line[i] && line[i] != '|')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '\"')
			line = double_quotes(line, &i, data->envp);
		if (line[i] == '\'')
			line = single_quotes(line, &i);
		if (line[i] == '$' && (line[i + 1] == '_' || ft_isalpha(line[i + 1])))
			line = env_replace(line, &i, data->envp);
		if (line[i] == '$' && line[i + 1] == '?')
			line = exit_code_replace(line, data);
		if ((line[i] == '>' || line[i] == '<') && line[i + 1])
			line = parse_redirects(line, &i, cmd, data);
		if (line[i] != '|')
			i++;
		else
			data->num_cmd++;
	}
	one_cmd = ft_substr(line, 0, i);
	cmd->cmd = ft_split(one_cmd, ' ');
	free (one_cmd);
	return (&line[i]);
}

int	parser(t_arg *data, char *line)
{
	int			i;
	t_command	*temp;

	i = 0;
	if (check_syntax(line))
	{
		data->errnum = 258;
		return (1);
	}
	data->cmd = new_command();
	data->num_cmd = 1;
	temp = data->cmd;
	line = parse_line(line, data, data->cmd);
	i = 0;
	while (line[i] && line[i] == '|')
	{
		data->cmd->next = new_command();
		data->cmd = data->cmd->next;
		data->num_cmd++;
		line = parse_line(&line[1], data, data->cmd);
	}
	data->cmd = temp;
	// ------------------
	// t_command	*temp2 = data->cmd;
	// int f = 0;
	// while (data->cmd)
	// {
	// 	while (data->cmd->cmd[f])
	// 	{
	// 		printf("cmd arg%d: %s\n", f, data->cmd->cmd[f]);
	// 		f++;
	// 	}
	// 	f = 0;
	// 	printf("--------\n");
	// 	data->cmd = data->cmd->next;
	// }
	// data->cmd = temp2;

	// t_redir *temp3 = data->redir;
	// while (data->redir)
	// {
	// 	printf("redir for cmd %d - name %s - target %d\n", data->redir->cmd, data->redir->name, data->redir->target);
	// 	data->redir = data->redir->data_next;
	// }
	// data->redir = temp3;
	// ------------------

	return (0);
}
