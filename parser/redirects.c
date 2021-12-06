/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 22:19:52 by fbeatris          #+#    #+#             */
/*   Updated: 2021/12/06 22:25:56 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	redir_w_space(char **arr, int *i, t_arg *data)
{
	if (ft_strcmp(arr[*i], ">") == 0 || ft_strcmp(arr[*i], ">>") == 0)
	{
		data->cmd->out->limiter = ft_strdup(arr[*i]);
		data->cmd->out->name = ft_strdup(arr[*i + 1]);
	}
	else if (ft_strcmp(arr[*i], "<") == 0)
	{
		data->cmd->in->limiter = ft_strdup(arr[*i]);
		data->cmd->in->name = ft_strdup(arr[*i + 1]);
	}
	while (arr[*i + 2])
	{
		arr[*i] = arr[*i + 2];
		(*i)++;
	}
//	free(arr[*i]);
	arr[*i] = NULL;
	if (arr[*i + 1])
	 	free(arr[*i + 1]);
	if (arr[*i + 2])
	 	free(arr[*i + 2]);
	// printf("i %d\n", *i);
}

static void	redir_wo_space(char **arr, int *i, t_arg *data)
{
	if (arr[*i][0] == '>')
	{
		data->cmd->out->limiter = ft_strdup(">");
		data->cmd->out->name = ft_strdup(&arr[*i][1]);
	}
	else if (arr[*i][0] == '<')
	{
		data->cmd->in->limiter = ft_strdup("<");
		data->cmd->in->name = ft_strdup(&arr[*i][1]);
	}
	while (arr[*i + 1])
	{
		arr[*i] = arr[*i + 1];
		(*i)++;
	}
	free(arr[*i]);
	arr[*i] = NULL;
	if (arr[*i + 1])
		free(arr[*i + 1]);
}

char **parse_redirects(char *line, t_arg *data)
{
	char	**arr;
	int		i;

	arr = ft_split(line, ' ');
	free(line);
	i = 0;
	while (arr[i])
	{
		if (ft_strcmp(arr[i], ">") == 0 || ft_strcmp(arr[i], ">>") == 0 || ft_strcmp(arr[i], "<") == 0)
			redir_w_space(arr, &i, data);
		else if (arr[i][0] == '>' || arr[i][0] == '<')
			redir_wo_space(arr, &i, data);
		i++;
	}
	// int j = 0;
	// while (arr[j])
	// {
	// 	printf("-%s-\n", arr[j]);
	// 	j++;
	// }
	// printf("j %d\n", j);
	return (arr);
}
