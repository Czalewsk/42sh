/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste_handler_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 03:48:02 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/29 04:09:24 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

inline void	init_paste_handler(char **space, t_buf *pasted, t_read *info)
{
	*space = ft_strnew(SIZE_READ);
	ft_memset(*space, ' ', SIZE_READ);
	g_sh.edition_state = PASTED;
	buff_handler(pasted, NULL, NULL, info);
}

inline void	read_and_bzero(t_key *entry, int *i)
{
	if (*i < entry->nread - 1)
		(*i)++;
	else
	{
		(*i) = 0;
		ft_bzero(entry, sizeof(t_key));
		read_key(entry);
	}
}
