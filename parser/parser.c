/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:09:43 by fbeatris          #+#    #+#             */
/*   Updated: 2021/12/18 06:37:18 by fbeatris         ###   ########.fr       */
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
	return (new);
}

char	*parse_line(char *line_const, t_arg *data, t_command *cmd)
{
	char	*line;
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
		// if (line[i] == '\\')
		// 	line = backslash(line, &i);
		if (line[i] == '$' && (line[i + 1] == '_' || ft_isalpha(line[i + 1])))
			line = env_replace(line, &i, data->envp);
		if ((line[i] == '>' || line[i] == '<') && line[i + 1])
			line = parse_redirects(line, &i, cmd);
		if (line[i] != '|')
			i++;
	}
	cmd->cmd = ft_split(line, ' ');
	return (&line[i]);
}

int	parser(t_arg *data, char *line)
{
	int			i;
	t_command	*temp;

	i = 0;
	if (check_syntax(line))
	{
		printf("syntax error\n");
		exit (1);
	}
	data->cmd = new_command();
	temp = data->cmd;
	line = parse_line(line, data, data->cmd);
	i = 0;
	while (line[i] && line[i] == '|')
	{
		data->cmd->next = new_command();
		data->cmd = data->cmd->next;
		line = parse_line(&line[1], data, data->cmd);
	}
	data->cmd = temp;
	
	return (0);
}
