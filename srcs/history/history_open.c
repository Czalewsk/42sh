/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_open.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:06:53 by bviala            #+#    #+#             */
/*   Updated: 2017/12/06 20:19:19 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		check_history_access(const char *file)
{
	struct stat buff;

	errno = 0;
	if (!stat(file, &buff))
	{
		if (S_ISREG(buff.st_mode) && (S_IRUSR & buff.st_mode))
			return (1);
		else
			return (0);
	}
	if (errno == 2)
		return (1);
	return (0);
}
