/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_comp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 12:19:21 by bviala            #+#    #+#             */
/*   Updated: 2018/03/05 23:48:58 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	comp_arrow_down(t_buf *cmd, t_read *info, t_key *entry)
{
	t_comp	*comp;
	t_ldl	*ldl;

	comp = g_sh.comp;
	ldl = get_current(comp->head);
	((t_select *)ldl->content)->is_current = 0;
	if (ldl->next)
		ldl = ldl->next;
	else
		ldl = comp->head->head;
	((t_select *)ldl->content)->is_current = 1;
	return (sh_comp(cmd, info, entry));
}

char	comp_arrow_up(t_buf *cmd, t_read *info, t_key *entry)
{
	t_ldl	*ldl;
	t_comp	*comp;

	comp = g_sh.comp;
	ldl = get_current(comp->head);
	((t_select *)ldl->content)->is_current = 0;
	if (ldl->prev)
		ldl = ldl->prev;
	else
		ldl = comp->head->tail;
	((t_select *)ldl->content)->is_current = 1;
	return (sh_comp(cmd, info, entry));
}

char	comp_arrow_right(t_buf *cmd, t_read *info, t_key *entry)
{
	t_ldl	*ldl;
	t_comp	*comp;
	int		i;

	comp = g_sh.comp;
	ldl = get_current(comp->head);
	((t_select *)ldl->content)->is_current = 0;
	i = comp->nb_file_col;
	while (i-- > 0)
	{
		if (ldl->next)
			ldl = ldl->next;
		else
		{
			i -= (comp->nb_file_col * (comp->nb_col) - comp->nb_file);
			if (i >= 0 || comp->nb_file_col == 1)
				ldl = comp->head->head;
		}
	}
	((t_select *)ldl->content)->is_current = 1;
	return (sh_comp(cmd, info, entry));
}

char	comp_arrow_left(t_buf *cmd, t_read *info, t_key *entry)
{
	t_ldl	*ldl;
	t_comp	*comp;
	int		i;

	comp = g_sh.comp;
	ldl = get_current(comp->head);
	((t_select *)ldl->content)->is_current = 0;
	i = comp->nb_file_col;
	while (i-- > 0)
	{
		if (ldl->prev)
			ldl = ldl->prev;
		else
		{
			i -= (comp->nb_file_col * (comp->nb_col) - comp->nb_file);
			ldl = comp->head->tail;
		}
	}
	((t_select *)ldl->content)->is_current = 1;
	return (sh_comp(cmd, info, entry));
}
