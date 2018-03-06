/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_comp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:09:31 by bviala            #+#    #+#             */
/*   Updated: 2018/03/05 18:05:57 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_ldl		*get_current(t_ldl_head *lst)
{
	t_ldl *ldl;

	ldl = lst ? lst->head : NULL;
	while (ldl)
	{
		if (((t_select *)ldl->content)->is_current)
			return (ldl);
		ldl = ldl->next;
	}
	return (ldl);
}

static int	current_index(t_ldl_head *head)
{
	t_ldl	*ldl;
	int		i;

	ldl = head ? head->head : NULL;
	i = 0;
	while (ldl)
	{
		if (((t_select *)ldl->content)->is_current)
			return (i);
		++i;
		ldl = ldl->next;
	}
	return (i);
}

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
		len = ((t_select *)ldl->content)->len + 1;
		if (len > max)
			max = len;
		ldl = ldl->next;
	}
	return (max);
}

void		calcul_display(t_comp *comp, t_read *info, t_buf *cmd)
{
	int prompt;

	if (!info->win_height)
		return ;
	comp->nb_file = comp->head->length;
	if (comp->nb_file > 2147483647)
		comp->nb_file = 2147483647;
	comp->len_max = get_len_max(comp->head);
	prompt = (info->prompt + ft_strlen_utf8(cmd->cmd) + comp->len_max)
		/ info->win_co;
	if ((info->prompt + ft_strlen_utf8(cmd->cmd) + comp->len_max)
			% info->win_co)
		prompt++;
	comp->win_height = info->win_height - prompt - 1;
	comp->nb_col_visible =
		(comp->nb_col_visible) ? comp->nb_col_visible : 1;
	comp->nb_file_col = comp->nb_file / comp->nb_col_visible;
	if (comp->nb_file_col > comp->win_height)
		comp->nb_file_col = comp->win_height;
	comp->nb_file_col = comp->nb_file_col ? comp->nb_file_col : 1;
	comp->nb_col = comp->nb_file / comp->nb_file_col;
	if ((comp->nb_file_col * comp->nb_col) < comp->nb_file)
		comp->nb_col++;
	comp->index_col = current_index(comp->head) / comp->nb_file_col;
}

char		sh_comp(t_buf *cmd, t_read *info, t_key *entry)
{
	t_ldl	*ldl;

	calcul_display(g_sh.comp, info, cmd);
	ldl = g_sh.comp->head->head;
	if (ldl)
	{
		if (g_sh.comp->head->length == 1 || g_sh.comp->ret)
			return (validate_completion(cmd, info, entry));
		if (g_sh.comp->first)
		{
			clear_prompt_comp(g_sh.comp);
			cursor_back_begin(info);
			prompt_display(info, 0);
			ft_putstr_fd(cmd->cmd, g_sh.fd_tty);
		}
		else
			g_sh.comp->first = 1;
		ft_putchar_fd('\n', g_sh.fd_tty);
		print_comp(g_sh.comp, info, cmd);
	}
	return (0);
}
