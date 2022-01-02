/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:09:43 by fbeatris          #+#    #+#             */
/*   Updated: 2022/01/02 20:50:47 by fbeatris         ###   ########.fr       */
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

void	parse_line(char **line, t_arg *data, t_command *cmd)
{
	char	*one_cmd;
	int		i;
	char	*new_line;
	char	*save_line;

	i = 0;
	save_line = *line;
	if ((*line)[i] == '|')
		(*line)++;
	// printf("start: |%s|\n", *line);
	parse_line_loop(line, data, cmd, &i);
	one_cmd = ft_substr(*line, 0, i, data);
	cmd->cmd = ft_split(one_cmd, ' ', data);
	free(one_cmd);
	new_line = ft_strdup(&(*line)[i], data);
	free(save_line);
	// printf("finish: |%s|\n", *line);
//	printf("new line: |%s|\n", new_line);

	*line = new_line;
	// printf("new line: |%s|\n", *line);
}

/* return 1 if syntax error */
int	parser(t_arg *data, char *read_line)
{
	int			i;
	t_command	*temp;
	char		*line;

	line = ft_strdup(read_line, data);
	free (read_line);
	if (!line)
		ft_exit(12, "malloc", data);
	i = 0;
	if (check_syntax(line, data))
		return (1);
	data->cmd = new_command();
	data->num_cmd = 1;
	temp = data->cmd;
	parse_line(&line, data, data->cmd);
	if (!line)
		ft_exit(12, "malloc", data);
	i = 0;
	// printf("parser line: |%s|\n--------\n", line);
	while (line[i] && line[i] == '|')
	{
		data->cmd->next = new_command();
		data->cmd = data->cmd->next;
		data->num_cmd++;
		parse_line(&line, data, data->cmd);
		if (!line)
			ft_exit(12, "malloc", data);
	}
	data->cmd = temp;
	free(line);
	return (0);
}
