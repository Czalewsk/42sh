/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_comp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:09:31 by bviala            #+#    #+#             */
/*   Updated: 2018/01/30 05:44:27 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	get_len_max(t_ldl_head *head)
{
	int		len;
	int 	max;
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
	return (max);
}

static void	calcul_display(t_comp *comp, t_read *info)
{
	if (!info->win_height)
		return ;
	comp->nb_item = comp->head->length;
	comp->len_max = get_len_max(comp->head);
}

static void	init_comp(t_buf *cmd)
{
	g_sh.edition_state = COMPLETION;
	if (!g_sh.comp)
	{
		g_sh.comp = ft_memalloc(sizeof(t_comp));
		g_sh.comp->search = ft_strdup(cmd->cmd);
		g_sh.comp->head = ft_ldl_new_list();
	}
}

char	sh_comp(t_buf *cmd, t_read *info, t_key *entry)
{
	(void)entry;

	DEBUG("COMP\n");
	init_comp(cmd);
//	if (!comp_status)
//	{
//		search_lala ; binaire et var ENV;
//	}
//	search ls;
	calcul_display(g_sh.comp, info);
//	print comp;
	return (0);
}
