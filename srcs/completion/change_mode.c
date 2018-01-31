/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 19:24:19 by bviala            #+#    #+#             */
/*   Updated: 2018/01/30 16:27:22 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char		history_to_completion(t_buf *cmd, t_read *info, t_key *entry)
{
	ft_ldl_clear(&g_sh.hist, &ft_strdel);
	g_sh.h_first = 0;
	ft_strdel(&(g_sh.h_save));
	g_sh.edition_state = COMPLETION;
	return (key_manager(cmd, info, entry));
}

static void	del_select(t_select *select)
{
	ft_strdel(&select->name);
	ft_strdel(&select->escaped);
	free(select);
	select = NULL;
}

char		completion_to_normal(t_buf *cmd, t_read *info, t_key *entry)
{
	g_sh.edition_state = NORMAL;
	if (g_sh.comp)
	{
		ft_ldl_clear(&g_sh.comp->head, &del_select);
		ft_strdel(&g_sh.comp->search);
		free(g_sh.comp);
		g_sh.comp = NULL;
	}
	return (key_manager(cmd, info, entry));
}

char		validate_completion(t_buf *cmd, t_read *info, t_key *entry)
{
	// display new string;
	return (completion_to_normal(cmd, info, entry));
}
