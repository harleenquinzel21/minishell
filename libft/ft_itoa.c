/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:36:35 by ogarthar          #+#    #+#             */
/*   Updated: 2021/12/27 16:32:41 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n, t_arg *data)
{
	int		i;
	int		len_n;
	char	*str;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648", data));
	len_n = ft_nbrlen(n);
	str = (char *)malloc(sizeof(char) * (len_n + 1));
	if (!str)
		ft_exit(12, "malloc", data);
	str[len_n] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		i++;
	}
	while (i < len_n--)
	{
		str[len_n] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
