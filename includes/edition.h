/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edition.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:43:07 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/14 17:23:25 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __EDITION_H
# define __EDITION_H

/*
** DEFINE READ
** SIZE_READ NE DOIT PAS ETRE INFERIEUR A 8
*/

# include "ft_sh.h"
# define SIZE_READ (12)
# define CTRL_KEY(k) ((k) & 0x1f)
# define DEL_KEY (2117294875l)
# define ABS(x) (x > 0 ? x : -x)

/*
** GLOBAL MACHINE A ETAT
*/

extern int			g_edition_state;

typedef enum		e_edition_state
{
	NORMAL, COMPLETION, HISTORY, EDITION_MAX_STATE
}					t_edition_state;

/*
** /!\ Insert Key_name before MAX_KEY /!\
*/

typedef enum		e_key_name
{
	ARROW_L, ARROW_R, ARROW_U, ARROW_D, QUIT, ENTER, DELETE, SUPPR, SHIFT_UP,
	SHIFT_DO, HOME, END, MAX_KEY
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
	size_t			total_char;
	long			curs_char;
}					t_read;

typedef struct		s_key
{
	int				nread;
	char			entry[SIZE_READ];
}					t_key;

typedef struct		s_buf
{
	char			*cmd;
	size_t			size_max;
	size_t			size_actual;
}					t_buf;

void				buff_handler(t_buf *cmd, t_key *entry);
char				read_line(t_buf *cmd, t_read *info);
void				read_key(t_key *entry);
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
void				cursor_back_home(t_read *info, int clean_screen);

#endif
