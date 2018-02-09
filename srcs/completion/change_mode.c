/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 19:24:19 by bviala            #+#    #+#             */
/*   Updated: 2018/02/08 22:55:29 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char		history_to_completion(t_buf *cmd, t_read *info, t_key *entry)
{
	ft_ldl_clear(&g_sh.hist, &ft_strdel);
	g_sh.h_first = 0;
	ft_strdel(&(g_sh.h_save));
	g_sh.edition_state = NORMAL;
	return (key_manager(cmd, info, entry));
}

static void	del_select(t_select **select)
{
	ft_strdel(&(*select)->name);
	ft_strdel(&(*select)->escaped);
	free(*select);
	select = NULL;
}

char		completion_to_normal(t_buf *cmd, t_read *info, t_key *entry)
{
	g_sh.edition_state = NORMAL;
	if (g_sh.comp)
	{
		ft_ldl_clear(&g_sh.comp->head, &del_select);
		ft_strdel(&g_sh.comp->search);
		ft_strdel(&g_sh.comp->path);
		free(g_sh.comp);
		g_sh.comp = NULL;
	}
	return (key_manager(cmd, info, entry));
}

char		validate_completion(t_buf *cmd, t_read *info, t_key *entry)
{
	t_ldl	*ldl;
	int		i;

	(void)entry;
	g_sh.edition_state = NORMAL;
	ldl = g_sh.comp->head->head;
	if (!(i = 0) && ldl)
	{
		ft_putchar('\n');
		print_comp(g_sh.comp, info);
		prompt_display(info, 0);
	}
	while (ldl && ++i != g_sh.comp->index)
		ldl = ldl->next;
	if (ldl && ((t_select *)ldl->content)->is_current)
		display_new_comp(cmd, info, ((t_select *)ldl->content));
	ft_ldl_clear(&g_sh.comp->head, &del_select);
	ft_strdel(&g_sh.comp->search);
	ft_strdel(&g_sh.comp->path);
	free(g_sh.comp);
	g_sh.comp = NULL;
	return (0);
}
