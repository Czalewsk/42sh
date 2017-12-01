/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:42:19 by bviala            #+#    #+#             */
/*   Updated: 2017/12/01 20:05:33 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static t_ldl_head	*g_list = NULL;
static t_ldl		*g_ldl = NULL;



//  close_history()
//	history_up(t_buf *cmd, t_read *info, t_key *entry)
//	history_do(t_buf *cmd, t_read *info, t_key *entry)

		history_init()

char	history_mode(t_buf *cmd, t_read *info, t_key *entry)
{
	if (!g_list)
		g_list = history_init();
}
