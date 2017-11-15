/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:48:05 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/15 18:47:24 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		debug(char *format, ...)
{
	int			fd;
	va_list		ap;

	fd = open(DEBUG_WINDOW, O_RDWR);
	va_start(ap, format);
	vdprintf(fd, format, ap);
	va_end(ap);
	close(fd);
	return (1);
}
