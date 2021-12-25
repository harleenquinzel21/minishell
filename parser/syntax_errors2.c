/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:13:54 by misha             #+#    #+#             */
/*   Updated: 2021/12/25 23:39:49 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
