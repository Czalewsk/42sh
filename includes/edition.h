/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edition.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:43:07 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/09 23:13:43 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __EDITION_H
# define __EDITION_H

# include "ft_sh.h"

/*
** DEFINE READ
*/

# define SIZE_READ (12)
# define CTRL_KEY(k) ((k) & 0x1f)
# define DEL_KEY (2117294875l)

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

#endif
