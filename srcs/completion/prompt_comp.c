/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_comp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 12:02:51 by bviala            #+#    #+#             */
/*   Updated: 2018/03/05 17:34:51 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		clear_prompt_comp(t_comp *comp)
{
	int		up;

	up = comp ? comp->nb_file_col + 1 + comp->part : 0;
	tputs(tparm(g_termcaps_cap[COL], 0), 0, &ft_putchar_termcap);
	if (up)
		tputs(tparm(g_termcaps_cap[NUP], up), 0, &ft_putchar_termcap);
	tputs(g_termcaps_cap[CLEAR], 0, &ft_putchar_termcap);
}

void		display_new_comp(t_buf *cmd, t_read *info, t_select *select)
{
	char	*curs;
	char	*new_cmd;
	int		len_path;
	int		len;

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
