/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 19:24:19 by bviala            #+#    #+#             */
/*   Updated: 2018/03/05 18:10:43 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	del_select(t_select **select)
{
	ft_strdel(&(*select)->name);
	ft_strdel(&(*select)->escaped);
	free(*select);
	select = NULL;
}

char		completion_to_normal(t_buf *cmd, t_read *info, t_key *entry)
{
	(void)entry;
	g_sh.edition_state = NORMAL;
	clear_prompt_comp((g_sh.comp && (g_sh.comp->head->length > 1)) ?
			g_sh.comp : NULL);
	prompt_display(info, 0);
	if (g_sh.comp)
	{
		ft_ldl_clear(&g_sh.comp->head, &del_select);
		ft_strdel(&g_sh.comp->search);
		ft_strdel(&g_sh.comp->path);
		free(g_sh.comp);
		g_sh.comp = NULL;
	}
	comp_reinit_tty(0);
	display_str(cmd, info, cmd->cmd, ft_strlen_utf8(cmd->cmd));
	return (key_manager(cmd, info, entry));
}

char		completion_to_normal_char(t_buf *cmd, t_read *info, t_key *entry)
{
	(void)entry;
	g_sh.edition_state = NORMAL;
	clear_prompt_comp((g_sh.comp && (g_sh.comp->head->length > 1)) ?
			g_sh.comp : NULL);
	prompt_display(info, 0);
	if (g_sh.comp)
	{
		ft_ldl_clear(&g_sh.comp->head, &del_select);
		ft_strdel(&g_sh.comp->search);
		ft_strdel(&g_sh.comp->path);
		free(g_sh.comp);
		g_sh.comp = NULL;
	}
	comp_reinit_tty(0);
	display_str(cmd, info, cmd->cmd, ft_strlen_utf8(cmd->cmd));
	return (1);
}

char		quit_completion(t_buf *cmd, t_read *info, t_key *entry)
{
	(void)entry;
	g_sh.edition_state = NORMAL;
	clear_prompt_comp((g_sh.comp && (g_sh.comp->head->length > 1)) ?
			g_sh.comp : NULL);
	prompt_display(info, 0);
	if (g_sh.comp)
	{
		ft_ldl_clear(&g_sh.comp->head, &del_select);
		ft_strdel(&g_sh.comp->search);
		ft_strdel(&g_sh.comp->path);
		free(g_sh.comp);
		g_sh.comp = NULL;
	}
	comp_reinit_tty(0);
	display_str(cmd, info, cmd->cmd, ft_strlen_utf8(cmd->cmd));
	return (0);
}

char		validate_completion(t_buf *cmd, t_read *info, t_key *entry)
{
	t_ldl	*ldl;

	(void)entry;
	g_sh.edition_state = NORMAL;
	ldl = (g_sh.comp) ? get_current(g_sh.comp->head) : NULL;
	clear_prompt_comp((g_sh.comp && (g_sh.comp->head->length > 1)) ?
			g_sh.comp : NULL);
	prompt_display(info, 0);
	comp_reinit_tty(0);
	if (ldl)
		display_new_comp(cmd, info, ((t_select *)ldl->content));
	else
		display_str(cmd, info, cmd->cmd, ft_strlen_utf8(cmd->cmd));
	if (g_sh.comp)
	{
		ft_ldl_clear(&g_sh.comp->head, &del_select);
		ft_strdel(&g_sh.comp->search);
		ft_strdel(&g_sh.comp->path);
		free(g_sh.comp);
		g_sh.comp = NULL;
	}
	return (0);
}
