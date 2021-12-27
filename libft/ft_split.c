/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:36:35 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/27 16:31:33 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wcount(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] == '\0')
			return (count);
		while (str[i] != c && str[i] != '\0')
			i++;
		count++;
	}
	return (count);
}

static int	ft_wlen(char const *str, char c)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i] == c)
		i++;
	while (str[i] != c && str[i] != '\0')
	{
		i++;
		size++;
	}
	return (size);
}

char	**ft_split(char const *str, char c, t_arg *data)
{
	int		i;
	int		j;
	int		count;
	char	**split;

	if (str == 0)
		return (0);
	j = 0;
	count = ft_wcount(str, c);
	i = 0;
	split = malloc(sizeof(char *) * (count + 1));
	if (!split)
		ft_exit(12, "malloc", data);
	while (count > 0)
	{
		while (*str == c)
			str++;
		split[j] = ft_substr(str, i, ft_wlen(str, c), data);
		str = str + ft_wlen(str, c);
		j++;
		count--;
	}
	split[j] = 0;
	return (split);
}
