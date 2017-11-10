/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 04:42:37 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/10 04:45:13 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		insert_char(t_buf *cmd, t_read *info, t_key *entry)
{
	(void)cmd;
	(void)info;
	(void)entry;
	write(1, entry->entry, entry->nread);
}
