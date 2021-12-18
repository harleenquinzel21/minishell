/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:09:43 by fbeatris          #+#    #+#             */
/*   Updated: 2021/12/18 03:30:46 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*parse_line(char *line_const, t_arg *data)
{
	int		i;
	char	*line;

	i = 0;
	line = ft_strdup(line_const);
	while (line[i])
	{
		if (line[i] == '\"')
			line = double_quotes(line, &i, data->envp);
		if (line[i] == '\'')
			line = single_quotes(line, &i);
		// if (line[i] == '\\')
		// 	line = backslash(line, &i);
		if (line[i] == '$' && (line[i + 1] == '_' || ft_isalpha(line[i + 1])))
			line = env_replace(line, &i, data->envp);
		if ((line[i] == '>' || line[i] == '<') && line[i + 1])
			line = parse_redirects(line, &i, data);
		i++;
	}
	return (line);
}

int	parser(t_arg *data, char *line)
{

	data->cmd->in = NULL;
	data->cmd->out = NULL;
	if (check_syntax(line))
	{
		printf("syntax error\n");
		exit (1);
	}
	line = parse_line(line, data);
	// printf("final line |%s|\n", line);
	data->cmd->cmd = ft_split(line, ' ');
	return (0);
}
