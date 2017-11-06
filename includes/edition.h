/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edition.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:43:07 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/06 15:44:28 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __EDITION_H
# define __EDITION_H

# include "42shell.h"

/*
** DEFINE READ
*/

# define SIZE_READ (12)
# define CTRL_KEY(k) ((k) & 0x1f)

typedef struct		s_read
{
	size_t			prompt;
	size_t			win_co;
	size_t			total_char;
	long			curs_char;
	long			curs_li;
	size_t			max_li;
	long			curs_co;
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

#endif
