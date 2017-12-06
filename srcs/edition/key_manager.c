/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 04:21:22 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/06 20:16:01 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char					sh_quit(t_buf *cmd, t_read *info, t_key *entry)
{
	close_history(1, cmd);
	(void)info;
	(void)entry;
	return (-1);
}

char					sh_validate_line(t_buf *cmd, t_read *info, t_key *entry)
{
	(void)entry;
	if (info->curs_char != (long)info->total_char)
	{
		info->curs_char = info->total_char;
		cursor_display_update(info, 0);
	}
	close_history(0, cmd);
	return (-2);
}

char					sh_stop_line(t_buf *cmd, t_read *info, t_key *entry)
{
	(void)cmd;
	(void)entry;
	if (info->curs_char != (long)info->total_char)
	{
		info->curs_char = info->total_char;
		cursor_display_update(info, 0);
	}
	return (-3);
}

/*
** Tableau de pointeurs sur fonctions correspondant aux touches de controles
**
** 1 -> Index pour debug
** 2 -> Enum de la touche
** 3 -> Nombre de char a tester pour la touche voulu
** 4 -> Tableau de char representant la touche
** 5 -> Tableau de de pointeurs sur fonctions correspondats aux differents state
**          de la machine a etat
*/
const t_key_map			g_key_map[] =
{
	{0, ARROW_L, 3, {27, 91, 68}, {&curs_move_hz, NULL, &curs_move_hz}},
	{1, ARROW_R, 3, {27, 91, 67}, {&curs_move_hz, NULL, &curs_move_hz}},
	{2, ARROW_U, 3, {27, 91, 65}, {&history_mode, NULL, &history_up}},
	{3, ARROW_D, 3, {27, 91, 66}, {NULL, NULL, &history_do}},
	{4, QUIT, 1, {CTRL_KEY('D')}, {&sh_quit, NULL, &sh_quit}},
	{5, ENTER, 1, {13}, {&sh_validate_line, NULL, &sh_validate_line}},
	{6, DELETE, 1, {127}, {&delete_char, NULL, &delete_char}},
	{7, SUPPR, 4, {27, 91, 51, 126}, {&suppr_char, NULL, &suppr_char}},
	{8, SHIFT_UP, 6, {27, 91, 49, 59, 50, 65}, {&curs_move_vt, NULL, &curs_move_vt}},
	{9, SHIFT_DO, 6, {27, 91, 49, 59, 50, 66}, {&curs_move_vt, NULL, &curs_move_vt}},
	{10, HOME, 3, {27, 91, 72}, {&edition_home_end, NULL, &edition_home_end}},
	{11, END, 3, {27, 91, 70}, {&edition_home_end, NULL, &edition_home_end}},
	{12, PAGE_UP, 4, {27, 91, 53, 126}, {&history_mode, NULL, &history_up}},
	{13, PAGE_DO, 4, {27, 91, 54, 126}, {NULL, NULL, &history_do}},
	{14, PASTE_KEYBOARD, 6, {27, 91, 50, 48, 48, 126}, {&paste_handler, NULL, &paste_handler}},
	{15, CTRL_C, 1, {CTRL_KEY('C')}, {&sh_stop_line, NULL, &sh_stop_line}}
};

static void				*key_token(t_key *entry)
{
	int		i;
	int		j;

	i = -1;
	while (++i < MAX_KEY)
	{
		j = 0;
		if (entry->nread >= g_key_map[i].key_size)
		{
			while (j < entry->nread && entry->entry[j] == g_key_map[i].key[j])
				j++;
			if (j == g_key_map[i].key_size)
				return (g_key_map[i].function[g_edition_state]);
		}
	}
	return (NULL);
}

char					key_manager(t_buf *cmd, t_read *info, t_key *entry)
{
	char		(*f)(t_buf *, t_read *, t_key *);
	char		ret;

	ret = 0;
	if ((f = key_token(entry)))
		ret = f(cmd, info, entry);
	if (!ret)
		ft_bzero(entry, sizeof(t_key));
	return (ret);
}
