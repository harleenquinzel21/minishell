/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_other.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 20:05:36 by fbeatris          #+#    #+#             */
/*   Updated: 2021/12/27 16:11:27 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	unclosed_quotes(char *line)
{
	int	i;
	int	quotes1;
	int	quotes2;

	i = 0;
	quotes1 = 0;
	quotes2 = 0;
	while (line[i])
	{
		if (line[i] == '\'' && quotes1 == 0)
			quotes1++;
		else if (line[i] == '\'')
			quotes1--;
		i++;
	}
	if (quotes1 || quotes2)
		return (1);
	return (0);
}

int	unclosed_double_quotes(char *line)
{
	int	i;
	int	quotes1;
	int	quotes2;

	i = 0;
	quotes1 = 0;
	quotes2 = 0;
	while (line[i])
	{
		if (line[i] == '\"' && quotes2 == 0)
			quotes2++;
		else if (line[i] == '\"')
			quotes2--;
		i++;
	}
	if (quotes1 || quotes2)
		return (1);
	return (0);
}

char	*other_syntax_cases(char *line)
{
	if (last_pipe(line))
		return ("minishell: syntax error: unexpected end of file");
	else if (unclosed_quotes(line))
		return ("minishell: unexpected EOF while looking for matching `\'\'");
	else if (unclosed_double_quotes(line))
		return ("minishell: unexpected EOF while looking for matching `\"\'");
	else
		return (NULL);
}
