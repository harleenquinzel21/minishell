/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:13:54 by misha             #+#    #+#             */
/*   Updated: 2021/12/26 00:04:31 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wrong_pipes(char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '|')
		return (1);
	while (line[i])
	{
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int	last_pipe(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (line[i] && line[i] == ' ')
		i--;
	if (line[i] == '|')
		return (1);
	return (0);
}

int	empty_redirect(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (line[i] && line[i] == ' ')
		i--;
	if (line[i] == '<' || line[i] == '>')
		return (1);
	return (0);
}

/*
char	two_redirects(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			if (line[i + 1] && (line[i + 1] == '<' || line[i + 1] == '>'))
				i += 2;
			else
				i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '>')
				return (1);
		}
		i++;
	}
	return (0);
}
*/

char	*syntax_cases(char *line)
{
	if (wrong_pipes(line))
		return ("minishell: syntax error near unexpected token `|\'");
	else if (last_pipe(line))
		return ("minishell: syntax error: unexpected end of file");
	else if (wrong_semicolon(line))
		return ("minishell: syntax error near unexpected token `;\'");
	else if (double_semicolon(line))
		return ("minishell: syntax error near unexpected token `;;\'");
	else if (unclosed_quotes(line))
		return ("minishell: unexpected EOF while looking for matching `\'\'");
	else if (unclosed_double_quotes(line))
		return ("minishell: unexpected EOF while looking for matching `\"\'");
	else if (empty_redirect(line))
		return ("minishell: syntax error near unexpected token `newline\'");
	else
		return ("ok");
}

int	check_syntax(char *line, t_arg *data)
{
	char	*msg;

	msg = ft_strdup(syntax_cases(line));
	if (ft_strcmp(msg, "ok") != 0)
	{
		printf("%s\n", msg);
		free(msg);
		data->errnum = 258;
		return (1);
	}
	else
		return (0);
}
