/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 20:22:40 by ogarthar          #+#    #+#             */
/*   Updated: 2021/11/21 17:06:00 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

char	*read_file(int fd, char *rem, char *buf)
{
	int	bytes;

	bytes = read(fd, buf, BUFFER_SIZE);
	while (bytes > 0)
	{
		buf[bytes] = '\0';
		rem = ft_strjoin_g(rem, buf);
		if (ft_strchr_nl(rem))
			return (rem);
		bytes = read(fd, buf, BUFFER_SIZE);
	}
	return (rem);
}

int	cut_nl_rem_to_line(char **line, char **rem, char *ptr_nl)
{
	char	*tmp;

	if (!ptr_nl)
	{
		*line = ft_strdup_g(*rem);
		free(*rem);
		*rem = 0;
		return (0);
	}
	*ptr_nl = '\0';
	ptr_nl++;
	*line = ft_strdup_g(*rem);
	tmp = ft_strdup_g(ptr_nl);
	free(*rem);
	*rem = tmp;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*rem[MAX_FD];
	char		buf[BUFFER_SIZE + 1];
	char		*ptr_nl;
	int			res;

	res = 0;
	if (fd < 0 || fd > MAX_FD - 1 || line == 0 || BUFFER_SIZE <= 0 \
	|| read(fd, buf, 0) < 0)
		return (-1);
	*line = ft_strdup_g("");
	if (!(*line))
		return (-1);
	rem[fd] = read_file(fd, rem[fd], buf);
	if (!(rem[fd]))
		return (0);
	if (*line)
	{
		free(*line);
		*line = 0;
	}
	ptr_nl = ft_strchr_nl(rem[fd]);
	res = cut_nl_rem_to_line(line, &rem[fd], ptr_nl);
	return (res);
}
