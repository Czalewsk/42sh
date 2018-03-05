/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 04:21:22 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/05 23:53:27 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char					sh_quit(t_buf *cmd, t_read *info, t_key *entry)
{
	close_history(cmd);
	(void)info;
	(void)entry;
	return (-1);
}

char					sh_validate_line(t_buf *cmd, t_read *info, t_key *entry)
{
	(void)entry;
	*(cmd->cmd + cmd->size_actual) = '\n';
	*(cmd->cmd + cmd->size_actual + 1) = '\0';
	if (info->curs_char != (long)info->total_char)
	{
		info->curs_char = info->total_char;
		cursor_display_update(info, 0);
	}
	write(g_sh.fd_tty, "\n", 1);
	close_history(cmd);
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
	write(g_sh.fd_tty, "\n", 1);
	return (-3);
}

/*
** Tableau de pointeurs sur fonctions correspondant aux touches de controles
**
** 1 -> Index pour debug
** 2 -> Enum de la touche
** 3 -> Nombre de char a tester pour la touche voulu
** 4 -> Tableau de char representant la touche
** 5 -> Tableau de pointeurs sur fonctions correspondants
**			aux differents etats de la machine a etat
** /!\ Ne pas oublier de rajouter un bzero de t_key entry dans les fonctions
** /!\ indexee par key_map et appelee par le key_manager
*/
const t_key_map			g_key_map[] =
{
	{0, ARROW_L, 3, {27, 91, 68},
		{&curs_move_hz, &comp_arrow_left, &curs_move_hz,
			&pasted_remove_highlight, &cpy_pst_mvt}},
	{1, ARROW_R, 3, {27, 91, 67},
		{&curs_move_hz, &comp_arrow_right, &curs_move_hz,
			&pasted_remove_highlight, &cpy_pst_mvt}},
	{2, ARROW_U, 3, {27, 91, 65},
		{&history_mode, &comp_arrow_up, &history_up, NULL,
			&pasted_remove_highlight}},
	{3, ARROW_D, 3, {27, 91, 66},
		{NULL, &comp_arrow_down, &history_do, NULL,
			&pasted_remove_highlight}},
	{4, QUIT, 1, {CTRL_KEY('D')},
		{&sh_quit, &quit_completion, &sh_quit, &sh_quit, &sh_quit}},
	{5, ENTER, 1, {13},
		{&sh_validate_line, &validate_completion, &sh_validate_line,
			&sh_validate_line, &cpy_cut_validate}},
	{6, DELETE, 1, {127}, {&delete_char, &completion_to_normal, &delete_char,
			&delete_char, &pasted_remove_highlight}},
	{7, SUPPR, 4, {27, 91, 51, 126},
		{&suppr_char, &completion_to_normal, &suppr_char, &suppr_char,
			&pasted_remove_highlight}},
	{8, SHIFT_UP, 6, {27, 91, 49, 59, 50, 65},
		{&curs_move_vt, &completion_to_normal, &curs_move_vt,
			&pasted_remove_highlight, &cpy_pst_mvt}},
	{9, SHIFT_DO, 6, {27, 91, 49, 59, 50, 66},
		{&curs_move_vt, &completion_to_normal, &curs_move_vt,
			&pasted_remove_highlight, &cpy_pst_mvt}},
	{10, HOME, 3, {27, 91, 72},
		{&edition_home_end, &completion_to_normal, &edition_home_end,
			&pasted_remove_highlight, &cpy_pst_mvt}},
	{11, END, 3, {27, 91, 70},
		{&edition_home_end, &completion_to_normal, &edition_home_end,
			&pasted_remove_highlight, &cpy_pst_mvt}},
	{12, PAGE_UP, 4, {27, 91, 53, 126},
		{&history_mode, &completion_to_normal, &history_up, NULL,
			&pasted_remove_highlight}},
	{13, PAGE_DO, 4, {27, 91, 54, 126},
		{NULL, &completion_to_normal, &history_do, NULL,
			&pasted_remove_highlight}},
	{14, PASTE_KEYBOARD, 6, {27, 91, 50, 48, 48, 126},
		{&paste_handler, &completion_to_normal, &paste_handler,
			&pasted_remove_highlight, &pasted_remove_highlight}},
	{15, CTRL_C, 1, {CTRL_KEY('C')},
		{&sh_stop_line, &completion_to_normal, &sh_stop_line, &sh_stop_line,
			&sh_stop_line}},
	{16, CTRL_R, 1, {CTRL_KEY('R')},
		{&history_ctrlr, &completion_to_normal, &history_ctrlr,
			&pasted_remove_highlight, &pasted_remove_highlight}},
	{17, TAB, 1, {9}, {&expansion_wrapper, &comp_arrow_down,
			&history_to_completion, &pasted_remove_highlight,
			&pasted_remove_highlight}},
	{18, SHIFT_ARROW_L, 6, {27, 91, 49, 59, 50, 68},
		{&sh_curs_move_word, &completion_to_normal, &sh_curs_move_word,
			&pasted_remove_highlight, &cpy_pst_mvt}},
	{19, SHIFT_ARROW_R, 6, {27, 91, 49, 59, 50, 67},
		{&sh_curs_move_word, &completion_to_normal, &sh_curs_move_word,
			&pasted_remove_highlight, &cpy_pst_mvt}},
	{20, F13, 6, {27, 91, 49, 59, 50, 80}, {&cpy_cut_intern,
			&completion_to_normal, &cpy_cut_intern, &pasted_remove_highlight,
			&cpy_cut_validate}},
	{21, F14, 6, {27, 91, 49, 59, 50, 81}, {&cpy_cut_intern,
			&completion_to_normal, &cpy_cut_intern, &pasted_remove_highlight,
			&cpy_cut_validate}},
	{22, F15, 6, {27, 91, 49, 59, 50, 82}, {&paste_intern,
			&completion_to_normal, &paste_intern, &pasted_remove_highlight,
			&pasted_remove_highlight}},
	{23, ESC, 1, {27}, {NULL, NULL, NULL, &pasted_remove_highlight,
			&pasted_remove_highlight}},
};

inline void				*key_token(t_key *entry)
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
				return (g_key_map[i].function[g_sh.edition_state]);
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
