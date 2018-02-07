/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curs_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 21:51:12 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/07 22:46:45 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int		curs_find_word_l(char *str, int curs_pos)
{
	char	*curs;

	curs = str + curs_pos;
	while (*curs && !ft_isspace(*curs))
		curs++;
	while (*curs && ft_isspace(*curs))
		curs++;
	return (curs - str);
}

static int		curs_find_word_r(char *str, int curs_pos)
{
	char	*curs;

	curs = str + curs_pos - 1;
	while (curs >= str && ft_isspace(*curs))
		curs--;
	while (curs >= str && !ft_isspace(*curs))
		curs--;
	return (curs - str + 1);
}

static void		curs_word_r(t_buf *cmd, t_read *info)
{
	if (!info->curs_char)
		return ;
	info->curs_char = curs_find_word_r(cmd->cmd, info->curs_char);
	cursor_display_update(info, 0);
}

static void		curs_word_l(t_buf *cmd, t_read *info)
{
	if (info->curs_char == (long)info->total_char)
		return ;
	info->curs_char = curs_find_word_l(cmd->cmd, info->curs_char);
	cursor_display_update(info, 0);
}

char			sh_curs_move_word(t_buf *cmd, t_read *info, t_key *entry)
{
	if (entry->entry[5] == 68)
		curs_word_r(cmd, info);
	else
		curs_word_l(cmd, info);
	ft_bzero(entry, sizeof(t_key));
	return (1);
}
