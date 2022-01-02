/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 20:02:15 by ogarthar          #+#    #+#             */
/*   Updated: 2022/01/02 16:45:09 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_structs(t_arg **data)
{
	(*data) = (t_arg *)malloc(sizeof (t_arg));
	if (!(*data))
		ft_exit(12, "malloc", NULL);
	(*data)->cmd = NULL;
	(*data)->redir = NULL;
	(*data)->envp = NULL;
	(*data)->num = 0;
	(*data)->num_cmd = 0;
	(*data)->errnum = 0;
	(*data)->fd = NULL;
}
