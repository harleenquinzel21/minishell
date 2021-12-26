/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:13:54 by misha             #+#    #+#             */
/*   Updated: 2021/12/26 20:14:58 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*second_wrong(char *line)
{
	if (line[1] && line[0] == '>' && line[1] == '>')
		return (">>");
	else if (line[1] && line[0] == '<' && line[1] == '<')
		return ("<<");
	else if (line[0] == '>')
		return (">");
	else if (line[0] == '<')
		return ("<");
	else
		return (NULL);
}

char	*wrong_redirects(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			i++;
			if (line[i] == '<' || line[i] == '>')
				i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '<' || line[i] == '>')
				return (second_wrong(&line[i]));
		}
		i++;
	}
	return (NULL);
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
