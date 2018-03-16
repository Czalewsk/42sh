/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrx_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:46:05 by thugo             #+#    #+#             */
/*   Updated: 2018/03/16 15:52:52 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrx_fd(int fd, int num, ...)
{
	va_list	ap;
	int		i;

	va_start(ap, num);
	i = -1;
	while (++i < num)
		ft_putstr_fd((char *)va_arg(ap, char *), fd);
	va_end(ap);
}
