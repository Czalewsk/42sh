/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 19:44:57 by maastie           #+#    #+#             */
/*   Updated: 2018/03/26 18:18:25 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char		sh_great(int lfd, int rfd)
{
	dup2(rfd, lfd);
	return (0);
}


char		sh_dgreat(int lfd, int rfd)
{
	dup2(rfd, lfd);
	return (0);
}

char		sh_less(int lfd, int rfd)
{
	if (dup2(rfd, lfd) == -1)
		return (1);
	return (0);
}

char		sh_lessand(int lfd, int rfd)
{
	if (dup2(dup(rfd), lfd) == -1)
		return (1);
	return (0);
}

char		sh_close(int lfd, int rfd)
{
	(void)rfd;
	if (close(lfd) == -1)
		return (1);
	return (0);
}

char		sh_greatand(int lfd, int rfd)
{
	if (dup2(dup(rfd), lfd) == -1)
		return (1);
	return (0);
}

char		sh_lessgreat(int lfd, int rfd)
{
	dup2(lfd, rfd);
	return (0);
}
