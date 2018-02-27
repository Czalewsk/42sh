/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_comp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 08:40:39 by bviala            #+#    #+#             */
/*   Updated: 2018/02/21 18:27:31 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		display_new_comp(t_buf *cmd, t_read *info, t_select *select)
{
	char	*curs;
	char	*new_cmd;
	int		len_path;
	int		len;

	DEBUG("display new comp\n");
	len = ft_strlen(select->escaped);
	len_path = ft_strlen(g_sh.comp->path);
	new_cmd = ft_strnew(ft_strlen(cmd->cmd) -
			(g_sh.comp_end - g_sh.comp_start) + len_path + len);
	curs = ft_strncat(new_cmd, cmd->cmd, g_sh.comp_start);
	if (g_sh.comp->path)
		curs = ft_strcat(curs, g_sh.comp->path);
	curs = ft_strcat(curs, select->escaped);
	curs = ft_strcat(curs, cmd->cmd + g_sh.comp_end);
	g_sh.comp_end = g_sh.comp_start + len_path + len;
	display_str(cmd, info, new_cmd, ft_strnlen_utf8(new_cmd, g_sh.comp_end));
	ft_strdel(&new_cmd);
}

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
	while (i++ < len_max)
		ft_putchar_fd(' ', g_sh.fd_tty);
}

static void	full_display_comp(t_comp *comp)
{
	int			row;
	int			col;
	t_ldl		*ldl;
	int			i;

	i = 1;
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
		ft_putchar_fd('\n', g_sh.fd_tty);
	}
}

static void	part_display_comp(t_comp *comp, int row, int col)
{
	t_ldl		*ldl;
	int			i;

	ldl = comp->head->head;
	i = comp->index;
	while (ldl && --i)
		ldl = ldl->next;
	i = comp->index;
	while (ldl && (row++ < (comp->nb_visible / comp->nb_col)))
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
		ft_putchar_fd('\n', g_sh.fd_tty);
	}
	ft_putendl_fd("--- More ---", g_sh.fd_tty);
}

void		print_comp(t_comp *comp, t_read *info)
{
	if (!comp->head || !comp->head->head ||
			(comp->head && comp->head->length == 1))
		return ;
	if (info->win_height > 1 && (int)info->win_co > comp->len_max - 1)
	{
		if (comp->nb_item > comp->nb_visible)
			part_display_comp(comp, 0, 0);
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
