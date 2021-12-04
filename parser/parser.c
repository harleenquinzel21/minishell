/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:09:43 by fbeatris          #+#    #+#             */
/*   Updated: 2021/12/04 17:58:38 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
незакрытые кавычки, незакрытые двойные, бэкслэш в конце,
два пайпа подряд, что еще?
*/
/*
static void	redir_w_space(char **arr, int *i)
{
	int		j;
	char	*out;
	char	*redir;

	j = 0;

	redir = ft_strdup(arr[*i]);
	if (ft_strcmp(arr[*i], ">") == 0)
		out = ft_strdup(arr[*i + 1]);
	while (arr[*i + 2])
	{
		arr[*i] = arr[*i + 2];
		i++;
	}
	arr[*i] = NULL;
	free(arr[i + 1]);
	free(arr[i + 2]);
}
*/
/*
void parse_redirects(char *line, char **arr)
{
//	char	**arr;
	int		i;
//	int		line_end;
	char	*in;
	char	*out;

	i = 0;
	arr = ft_split(line, ' ');	//еще таб разделитель
	// while (arr[i])
	// {
	// 	if (ft_strcmp(arr[i], ">") == 0 || ft_strcmp(arr[i], ">>") == 0)
	// 		redir_w_space(arr, &i);
	// 	else if (ft_strcmp(arr[i], "<") == 0)
	// 		back_redir_w_space(arr, &i);
	// 	else if (arr[i][0] == '>')
	// 		redir_wo_space(arr, &i);
	// 	else if (arr[i][0] == '<')
	// 		back_redir_wo_space(arr, &i);
	// 	i++;
	// }
//	return ();
}
*/


int	parser(char **envp, t_arg *data, char *line) // ctrl-D, ctrl+C, ctrl+slash
{
	
		if (check_syntax(line))
		{
			printf("syntax error\n");
			exit (1);
		}
		
		line = parse_line(line, envp);

		data->cmd->cmd = ft_split(line, ' ');
		
		free(line);


	return (0);
}
