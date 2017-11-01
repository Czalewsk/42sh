/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 12:05:36 by bviala            #+#    #+#             */
/*   Updated: 2017/09/26 12:15:22 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnstr_fd(char const *str, int n, int fd)
{
	int		len;

	if (!str || !n)
		return ;
	len = ft_strlen(str);
	n = (len < n) ? len : n;
	if (n > 0)
		write(fd, str, n);
	else
		write(fd, str, len + n);
}

void	ft_putnstr(char const *str, int n)
{
	int		len;

	if (!str || !n)
		return ;
	len = ft_strlen(str);
	n = (len < n) ? len : n;
	if (n > 0)
		write(1, str, n);
	else
		write(1, str, len + n);
}
