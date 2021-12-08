/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:13:54 by misha             #+#    #+#             */
/*   Updated: 2021/12/07 20:38:24 by fbeatris         ###   ########.fr       */
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
		return (1);
	return (0);
}

static int	pipes_slash(char *line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (line[++i])
	{
		if (line[i] == '|' && line[i + 1] == '|')
			return (1);
	}
	i = 0;
	j = ft_strlen(line) - 1;
	tmp = ft_strtrim(line, "\t ");
	if (tmp[i] == '|' || tmp[j] == '|' || \
		(tmp[j] == '\\' && tmp[j - 1] != '\\'))
	{
		free(tmp);
		return (1);
	}
	else
	{
		free(tmp);
		return (0);
	}
}

int	check_syntax(char *line)
{
	if (pipes_slash(line))
		return (1);
	if (unclosed_quotes(line))
		return (1);
	return (0);
}
