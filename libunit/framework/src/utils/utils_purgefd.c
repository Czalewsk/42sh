/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_purgefd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 19:28:42 by thugo             #+#    #+#             */
/*   Updated: 2017/04/11 19:43:33 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

void	utils_purgefd(const int fd)
{
	int	savefcntl;
	char buffer[32];

	savefcntl = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, O_NONBLOCK);
	while (read(fd, buffer, 32) > 0);
	fcntl(fd, F_SETFL, savefcntl);
}
