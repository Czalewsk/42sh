/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:17:27 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/08 19:40:28 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		buff_handler(t_buf *cmd, t_key *entry)
{
	if (!entry)
	{
		cmd->size_max = SIZE_BUF_CMD;
		cmd->size_actual = 0;
		cmd->cmd = ft_strnew(SIZE_BUF_CMD);
		return ;
	}
	while (entry->nread + cmd->size_actual >= cmd->size_max - 1)
	{
		cmd->size_max *= 2;
		cmd->cmd = ft_memrealloc(cmd->cmd, cmd->size_actual, cmd->size_max);
	}
}
