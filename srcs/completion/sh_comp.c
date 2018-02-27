/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_comp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:09:31 by bviala            #+#    #+#             */
/*   Updated: 2018/02/21 16:24:33 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	get_len_max(t_ldl_head *head)
{
	int		len;
	int		max;
	t_ldl	*ldl;

	len = 0;
	max = 1;
	ldl = head->head;
	while (ldl)
	{
		len = ((t_select *)ldl->content)->len;
		if (len > max)
			max = len;
		ldl = ldl->next;
	}
	return (max + 1);
}

static void	calcul_display(t_comp *comp, t_read *info, t_buf *cmd)
{
	int prompt;

	if (!info->win_height)
		return ;
	comp->nb_item = comp->head->length;
	if (comp->nb_item > 2147483647)
		comp->nb_item = 2147483647;
	comp->len_max = get_len_max(comp->head);
	prompt = (info->prompt + ft_strlen_utf8(cmd->cmd) + comp->len_max)
		/ info->win_co + 1;
	comp->nb_col = info->win_co / comp->len_max;
	if (!comp->nb_col)
		comp->nb_col = 1;
	comp->nb_row = comp->nb_item / comp->nb_col + 1;
	if (comp->nb_row == 0)
		comp->nb_row = 1;
	comp->nb_visible =
		((info->win_height - prompt)) * comp->nb_col;
}

char		sh_comp(t_buf *cmd, t_read *info, t_key *entry)
{
	t_ldl	*ldl;
	int		i;

	calcul_display(g_sh.comp, info, cmd);
	g_sh.comp->index = (g_sh.comp->index < g_sh.comp->nb_item) ?
		(g_sh.comp->index + 1) : 1;
	ldl = g_sh.comp->head->head;
	if (ldl)
	{
		DEBUG("coucou");
		info->curs_char = info->total_char;
		cursor_display_update(info, 0);
		info->curs_char = 0;
		ft_putchar_fd('\n', g_sh.fd_tty);
		print_comp(g_sh.comp, info);
		prompt_display(info, 0);
		if (g_sh.comp->head->length == 1)
			return (quit_completion(cmd, info, entry));
	}
	i = 0;
	while (ldl && ++i != g_sh.comp->index)
		ldl = ldl->next;
	if (ldl && ((t_select *)ldl->content)->is_current)
		display_new_comp(cmd, info, ((t_select *)ldl->content));
	return (0);
}