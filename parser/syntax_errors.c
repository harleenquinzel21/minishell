/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:13:54 by misha             #+#    #+#             */
/*   Updated: 2021/12/03 21:37:43 by fbeatris         ###   ########.fr       */
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
		if (line[i] == '\"' && quotes2 == 0)
			quotes2++;
		else if (line[i] == '\"')
			quotes2--;
		i++;
	}
	if (quotes1 || quotes2)
		return (1);	//errno
	return (0);
}

static int	pipes_slash(char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[++i])
	{
		if (line[i] == '|' && line[i + 1] == '|')
			return (1);
	}
	i = 0;
	j = ft_strlen(line) - 1;
	line = ft_strtrim(line, "\t ");
	// while (line[i] && (line[i] == ' ' || line[i] == '\t'))
	// 	i++;
	// while (j >= 0 && (line[j] == ' ' || line[j] == '\t'))
	// 	j--;
	if (line[i] == '|' || line[j] == '|' || (line[j] == '\\' && line[j - 1] != '\\'))
		return (1);	
	else
		return (0);
}

int	check_syntax(char *line)
{
	if (pipes_slash(line))
		return (1);	//errno
	if (unclosed_quotes(line))
		return (1);	//errno
	return (0);
}
