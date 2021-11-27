/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 20:22:53 by ogarthar          #+#    #+#             */
/*   Updated: 2021/11/21 17:06:23 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

char	*ft_strchr_nl(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (str);
		str++;
	}
	return (0);
}

char	*ft_strdup_g(char *str)
{
	char	*new;
	size_t	size;
	int		i;

	i = 0;
	size = ft_strlen(str) + 1;
	new = (char *)malloc(sizeof(char) * size);
	if (!(new))
		return (0);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strjoin_g(char *rem, char *buf)
{
	char	*res;
	int		i;
	int		j;

	if (!rem)
		return (ft_strdup_g(buf));
	res = (char *)malloc(sizeof(char) * (ft_strlen(rem) + ft_strlen(buf) + 1));
	if (!res)
		return (0);
	i = 0;
	j = 0;
	while (rem[j])
		res[i++] = rem[j++];
	j = 0;
	while (buf[j])
		res[i++] = buf[j++];
	free(rem);
	res[i] = '\0';
	return (res);
}
