/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:09:43 by fbeatris          #+#    #+#             */
/*   Updated: 2022/01/06 23:50:35 by fbeatris         ###   ########.fr       */
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

void	parse_line_loop(char **line, t_arg *data, t_command *cmd, int *i)
{
	while ((*line)[*i] && (*line)[*i] != '|')
	{
		while ((*line)[*i] == ' ')
			(*i)++;
		if ((*line)[*i] == '\"')
			(*line) = double_quotes((*line), i, data->envp, data);
		if ((*line)[*i] == '\'')
			(*line) = single_quotes((*line), i, data);
		if ((*line)[*i] == '$' && ((*line)[*i + 1] == '_' || \
			ft_isalpha((*line)[*i + 1])))
			(*line) = env_replace((*line), i, data->envp, data);
		if ((*line)[*i] == '$' && (*line)[*i + 1] == '?')
			(*line) = exit_code_replace((*line), data);
		if (((*line)[*i] == '>' || (*line)[*i] == '<') && (*line)[(*i) + 1])
			(*line) = parse_redirects((*line), i, cmd, data);
		if ((*line)[*i] != '|')
			(*i)++;
		else
			data->num_cmd++;
	}
}

char	*parse_line(char **line, t_arg *data, t_command *cmd)
{
	char	*one_cmd;
	int		i;
	int		start;
	char	*new_line;

	i = 0;
	start = 0;
	if ((*line)[i] == '|')
	{
		i++;
		start++;
	}
	parse_line_loop(line, data, cmd, &i);
	one_cmd = ft_substr(*line, start, i, data);
	cmd->cmd = ft_split(one_cmd, ' ', data);
	free(one_cmd);
	new_line = ft_strdup(&(*line)[i], data);
	free(*line);
	return (new_line);
}

/* return 1 if syntax error */
int	parser(t_arg *data, char *line)
{
	t_command	*temp;

	if (!line)
		ft_exit(12, "malloc", data);
	if (check_syntax(line, data))
		return (1);
	data->cmd = new_command();
	data->num_cmd = 1;
	temp = data->cmd;
	line = parse_line(&line, data, data->cmd);
	if (!line)
		ft_exit(12, "malloc", data);
	while (line[0] && line[0] == '|')
	{
		data->cmd->next = new_command();
		data->cmd = data->cmd->next;
		data->num_cmd++;
		line = parse_line(&line, data, data->cmd);
		if (!line)
			ft_exit(12, "malloc", data);
	}
	data->cmd = temp;
	free(line);
	return (0);
}
