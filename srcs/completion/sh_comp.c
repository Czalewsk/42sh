/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_comp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:09:31 by bviala            #+#    #+#             */
/*   Updated: 2018/02/07 18:07:41 by bviala           ###   ########.fr       */
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
	return (max + 1);
}

static void	calcul_display(t_comp *comp, t_read *info)
{
	if (!info->win_height)
		return ;
	comp->nb_item = comp->head->length;
	comp->len_max = get_len_max(comp->head);
	comp->nb_col = info->win_co / comp->len_max;
	if (!comp->nb_col)
		comp->nb_col = 1;
	comp->nb_row = comp->nb_item / comp->nb_col;
	if (comp->nb_row == 0)

		comp->nb_row = 1;
	if (comp->nb_row > (int)info->win_height)
		comp->nb_visible =
			(comp->nb_row / (info->win_height - 1)) * comp->nb_col;
	else
		comp->nb_visible = comp->nb_row;
}

char	sh_comp(t_buf *cmd, t_read *info, t_key *entry)
{
	t_ldl 	*ldl;
	int		i;

	(void)entry;
//	DEBUG("COMP entree comp->index |%d|\n", g_sh.comp->index);
//	if (!comp_status)
//	{
//		search_lala ; binaire et var ENV;
//	}
	calcul_display(g_sh.comp, info);
	if (g_sh.comp->index < g_sh.comp->nb_item)
		g_sh.comp->index++;
	else
		g_sh.comp->index = 1;
	DEBUG("COMP sortie comp->index |%d| item |%d|\n", g_sh.comp->index, g_sh.comp->nb_item);
	ft_putchar('\n');
	print_comp(g_sh.comp, info);
	prompt_display(info, 0);
	ldl = g_sh.comp->head->head;
	i = 0;
	while (ldl && ++i != g_sh.comp->index)
		ldl = ldl->next;
	if (ldl && ((t_select *)ldl->content)->is_current)
		display_new_comp(cmd, info, ((t_select *)ldl->content));
	return (0);
}

char	first_comp(t_buf *cmd, t_read *info, t_key *entry, char *to_search)
{
	g_sh.edition_state = COMPLETION;
	g_sh.comp = ft_memalloc(sizeof(t_comp));
	g_sh.comp->search = ft_strdup(to_search);
//	DEBUG("comp->search |%s| escape |%s|\n", g_sh.comp->search, escape_it(g_sh.comp->search));
	g_sh.comp->head = ft_ldl_new_list();
	add_ls(g_sh.comp, g_sh.comp->head, NULL);
	return (sh_comp(cmd, info, entry));
}
