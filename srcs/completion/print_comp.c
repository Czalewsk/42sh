/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_comp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 08:40:39 by bviala            #+#    #+#             */
/*   Updated: 2018/02/07 18:08:06 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		display_new_comp(t_buf *cmd, t_read *info, t_select *select)
{
	char *curs;
	char *new_cmd;

	new_cmd = ft_strnew(ft_strlen_utf8(cmd->cmd) -
			(g_sh.comp_end - g_sh.comp_start) + select->len);
	if (g_sh.comp_start)
		curs = ft_strncat(new_cmd, cmd->cmd, g_sh.comp_start - cmd->cmd);
	else
		curs = new_cmd;
	curs = ft_strcat(curs, select->escaped);
	if (g_sh.comp_end)
		curs = ft_strcat(curs, g_sh.comp_end);
	display_str(cmd, info, new_cmd, (g_sh.comp_start - cmd->cmd) + select->len);
	ft_strdel(&new_cmd);
}

static void	print_item(t_select *select, int len_max, int i)
{
	if (select->is_current)
	{
		ft_putstr(BLACK);
		ft_putstr(F_WHITE);
	}
	else if (select->color)
	{
		if ((select->color & DIR_C) && !(select->color & WRI_C))
		{
			ft_putstr(T_BOLD);
			ft_putstr(CYAN);
		}
		else if (!(select->color & DIR_C) && (select->color & BIN_C))
			ft_putstr(RED);
		if (select->color & WRI_C)
		{
			ft_putstr(F_YELLOW);
			ft_putstr(BLACK);
		}
	}
	ft_putstr(select->name);
	ft_putstr(C_DEFAULT);
	while (i++ < len_max)
		ft_putchar(' ');
}

static void part_display_comp(t_comp *comp, t_read *info)
{
	(void)comp;
	(void)info;
	return ;
}

static void	full_display_comp(t_comp *comp)
{
	int			row;
	int			col;
	t_ldl		*ldl;
	int			i;

	i = 1;
	DEBUG("full display\n");
	if (!comp->head || !comp->head->head)
		return ;
	ldl = comp->head->head;
	row = 0;
	while (ldl && (row++ < comp->nb_row))
	{
		col = 0;
		while (ldl && (col++ < comp->nb_col))
		{
			((t_select *)ldl->content)->is_current = (i == comp->index) ? 1 : 0;
			print_item(ldl->content, comp->len_max,
					(int)((t_select *)ldl->content)->len);
			ldl = ldl->next;
			i++;
		}
		ft_putchar('\n');
	}
}

void	print_comp(t_comp *comp, t_read *info)
{
	if (info->win_height > 1 && (int)info->win_co > comp->len_max - 1)
	{
		if (comp->nb_row > comp->nb_visible)
		{
			DEBUG("OUIIIIIIIIIIIIIII\n");
			part_display_comp(comp, info);
		}
		else
			full_display_comp(comp);
	}
	else
	{
		tputs(g_termcaps_cap[CLEAR_ALL], 0, &ft_putchar_termcap);
		ft_putendl_fd(RED, 2);
		ft_putendl_fd("Too Small", 2);
		ft_putendl_fd(C_DEFAULT, 2);
	//	g_sh.exitstatus = code FAILURE correspondant
	}
}
