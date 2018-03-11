/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_comp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 08:40:39 by bviala            #+#    #+#             */
/*   Updated: 2018/03/05 18:09:41 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	print_item(t_select *select, int len_max, int i)
{
	if (select->is_current)
	{
		ft_putstr_fd(BLACK, g_sh.fd_tty);
		ft_putstr_fd(F_WHITE, g_sh.fd_tty);
	}
	else if (select->color)
	{
		if ((select->color & DIR_C) && !(select->color & WRI_C))
		{
			ft_putstr_fd(T_BOLD, g_sh.fd_tty);
			ft_putstr_fd(CYAN, g_sh.fd_tty);
		}
		else if (!(select->color & DIR_C) && (select->color & BIN_C))
			ft_putstr_fd(RED, g_sh.fd_tty);
		if (select->color & WRI_C)
		{
			ft_putstr_fd(F_YELLOW, g_sh.fd_tty);
			ft_putstr_fd(BLACK, g_sh.fd_tty);
		}
	}
	ft_putstr_fd(select->name, g_sh.fd_tty);
	ft_putstr_fd(C_DEFAULT, g_sh.fd_tty);
	while (++i < len_max)
		ft_putchar_fd(' ', g_sh.fd_tty);
}

void		print_one_file(t_ldl_head *lst, int file, int len)
{
	t_ldl	*ldl;
	int		index;
	int		i;

	index = 0;
	ldl = (lst) ? lst->head : NULL;
	while (ldl && index != file)
	{
		ldl = ldl->next;
		++index;
	}
	if (ldl && index == file)
		print_item(ldl->content, len, ((t_select *)ldl->content)->len);
	else
	{
		i = -1;
		while (++i < len)
			ft_putchar_fd(' ', g_sh.fd_tty);
	}
}

static void	full_display_comp(t_comp *comp)
{
	int			row;
	int			col;

	if (!comp->head || !comp->head->head)
		return ;
	row = -1;
	while (++row < comp->nb_file_col)
	{
		col = -1;
		while (++col < comp->nb_col)
			print_one_file(comp->head,
					(col * comp->nb_file_col) + row, comp->len_max);
		ft_putchar_fd('\n', g_sh.fd_tty);
	}
}

static void	part_display_comp(t_comp *comp)
{
	int		row;
	int		col;
	int		index;

	tputs(g_termcaps_cap[CLEAR_ALL], 0, &ft_putchar_termcap);
	row = -1;
	while (++row < comp->nb_file_col)
	{
		col = comp->index_col - 1;
		index = -1;
		while (++col < comp->nb_col && ++index < comp->nb_col_visible)
			print_one_file(comp->head, col * comp->nb_file_col + row,
					comp->len_max);
		col = -1;
		while (++index < comp->nb_col_visible)
			print_one_file(comp->head, ++col * comp->nb_file_col + row,
					comp->len_max);
		ft_putchar_fd('\n', g_sh.fd_tty);
	}
	ft_putendl_fd("--- More ---", g_sh.fd_tty);
}

void		print_comp(t_comp *comp, t_read *info, t_buf *cmd)
{
	if (!comp->head || !comp->head->head ||
			(comp->head && comp->head->length == 1))
		return ;
	if (comp->win_height > 1 && (int)info->win_co > comp->len_max - 1)
	{
		calcul_display(comp, info, cmd);
		if (comp->nb_col > comp->nb_col_visible)
			part_display_comp(comp);
		else
			full_display_comp(comp);
	}
	else
	{
		tputs(g_termcaps_cap[CLEAR_ALL], 0, &ft_putchar_termcap);
		ft_putendl_fd(RED, 2);
		ft_putendl_fd("Too Small", 2);
		ft_putendl_fd(C_DEFAULT, 2);
	}
}
