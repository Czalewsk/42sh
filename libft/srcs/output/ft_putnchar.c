/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 13:59:28 by bviala            #+#    #+#             */
/*   Updated: 2017/12/14 14:13:22 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnchar_fd(char const c, int n, int fd)
{
	int		i;

	if (!c || !n)
		return ;
	i = 0;
	while (i++ < n)
		write(fd, &c, n);
}

void	ft_putnchar(char const c, int n)
{
	int		i;

	if (!c || !n)
		return ;
	i = 0;
	while (i++ < n)
		write(1, &c, n);
}
