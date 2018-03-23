/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edition.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:43:07 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/21 19:34:45 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __EDITION_H
# define __EDITION_H

/*
** DEFINE READ
** SIZE_READ NE DOIT PAS ETRE INFERIEUR A 8
*/

# include "ft_sh.h"
# include <sys/ioctl.h>
# define SIZE_READ (12)
# define SIZE_BUFF (SIZE_READ * 2)
# define CTRL_KEY(k) ((k) & 0x1f)
# define DEL_KEY (2117294875l)
# define ABS(x) (x > 0 ? x : -x)

/*
** GLOBAL MACHINE A ETAT
*/

typedef enum		e_edition_state
{
	NORMAL, COMPLETION, HISTORY, PASTED, COPY_PASTE, EDITION_MAX_STATE
}					t_edition_state;

/*
** /!\ Insert Key_name before MAX_KEY /!\
*/

typedef enum		e_key_name
{
	ARROW_L, ARROW_R, ARROW_U, ARROW_D, QUIT, ENTER, DELETE, SUPPR, SHIFT_UP,
	SHIFT_DO, HOME, END, PAGE_UP, PAGE_DO, PASTE_KEYBOARD, CTRL_C, CTRL_R,
	TAB, SHIFT_ARROW_L, SHIFT_ARROW_R, F13, F14, F15, ESC, MAX_KEY
}					t_key_name;

typedef struct		s_key_map
{
	int				nb;
	int				key_name;
	int				key_size;
	char			key[SIZE_READ];
	void			*function[EDITION_MAX_STATE];
}					t_key_map;

typedef struct		s_read
{
	size_t			prompt;
	size_t			win_co;
	size_t			win_height;
	size_t			total_char;
	long			curs_char;
}					t_read;

typedef struct		s_key
{
	int				nread;
	char			entry[SIZE_BUFF];
}					t_key;

typedef struct		s_buf
{
	char			*cmd;
	size_t			size_max;
	size_t			size_actual;
}					t_buf;

char				buff_handler(t_buf *cmd, t_key *entry, char *str,
		t_read *info);
char				read_line(t_buf *cmd, t_read *info);
char				read_key(t_key *entry);
char				paste_handler(t_buf *cmd, t_read *info, t_key *entry);
char				insert_char(t_buf *cmd, t_read *info, t_key *entry);
char				key_manager(t_buf *cmd, t_read *info, t_key *entry);
void				hrz_deplacement(t_buf *cmd, t_read *info, t_key *entry);
char				curs_move_hz(t_buf *cmd, t_read *info, t_key *entry);
void				cursor_display_update(t_read *info, int write);
char				delete_char(t_buf *cmd, t_read *info, t_key *entry);
char				suppr_char(t_buf *cmd, t_read *info, t_key *entry);
char				curs_move_vt(t_buf *cmd, t_read *info, t_key *entry);
char				edition_home_end(t_buf *cmd, t_read *info, t_key *entry);
void				display_str(t_buf *cmd, t_read *info,
		char *str, size_t pos_cur);
void				cursor_back_home(t_read *info, char after_prompt);
int					sh_curs_unicode(char *str, int index, int end);
void				add_str(t_buf *cmd, t_read *info, char *str);
char				test_print(t_buf *cmd, t_read *info, t_key *entry);
void				info_init(t_read *info);
char				test_prompt_add(t_buf *cmd, t_read *info, t_key *entry);
void				cursor_back_begin(t_read *info);
char				expansion_wrapper(t_buf *cmd, t_read *info, t_key *entry);
char				wrapper_is_arg(t_buf *cmd);
char				sh_curs_move_word(t_buf *cmd, t_read *info, t_key *entry);
char				pasted_remove_highlight(t_buf *cmd, t_read *info,
		t_key *entry);
char				pasted_remove_highlight_char(t_buf *cmd, t_read *info,
		t_key *entry);
char				cpy_cut_intern(t_buf *cmd, t_read *info, t_key *entry);
char				cpy_pst_mvt(t_buf *cmd, t_read *info, t_key *entry);
char				cpy_cut_validate(t_buf *cmd, t_read *info, t_key *entry);
char				paste_intern(t_buf *cmd, t_read *info, t_key *entry);
void				buff_max_char_init(t_read *info);
void				*key_token(t_key *entry);
char				sh_stop_line(t_buf *cmd, t_read *info, t_key *entry);
char				sh_quit_ctrld(t_buf *cmd, t_read *info, t_key *entry);

#endif
