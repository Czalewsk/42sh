/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_termcap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 19:37:12 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/07 18:29:14 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		g_termcps_fd = 0;

int	ft_putchar_termcap(int c)
{
	write(g_termcps_fd, &c, 1);
	return (1);
}
