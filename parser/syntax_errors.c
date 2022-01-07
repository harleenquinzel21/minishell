/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:13:54 by misha             #+#    #+#             */
/*   Updated: 2022/01/07 02:42:01 by fbeatris         ###   ########.fr       */
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
		if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			i++;
			if (line[i] && line[i] == '|')
				return (0);
			if (line[i] == '>' || line[i] == '<')
				i++;
			while (line[i] && !ft_isalnum(line[i]) && line[i] != '|')
				i++;
			if (line[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int	wrong_semicolon(char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == ';')
		return (1);
	while (line[i])
	{
		if (line[i] == ';')
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == ';')
				return (1);
		}
		i++;
	}
	return (0);
}

int	double_semicolon(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i + 1] && line[i] == ';' && line[i + 1] == ';')
			return (1);
		i++;
	}
	return (0);
}

char	*unexpected_token(char *line)
{
	if (line[0] == '|' && line[1] == '|')
		return ("||");
	if (wrong_pipes(line))
		return ("|");
	else if (double_semicolon(line))
		return (";;");
	else if (wrong_semicolon(line))
		return (";");
	else if (wrong_redirects(line))
		return (wrong_redirects(line));
	else if (empty_redirect(line))
		return ("newline");
	else
		return (NULL);
}

int	check_syntax(char *line, t_arg *data)
{
	if (unexpected_token(line))
	{
		printf("minishell: syntax error near unexpected token `%s\'\n", \
			unexpected_token(line));
		data->errnum = 258;
		return (1);
	}
	else if (other_syntax_cases(line))
	{
		printf("%s\n", other_syntax_cases(line));
		data->errnum = 258;
		return (1);
	}
	else
		return (0);
}
