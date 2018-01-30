/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:15:01 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/30 05:00:42 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_SH_H
# define __FT_SH_H

# include "libft.h"
# include <termcap.h>
# include <curses.h>
# include <term.h>
# include <stdlib.h>
# include <wctype.h>
# include <string.h>
# include <errno.h>
# include <xlocale.h>
# include <locale.h>
# include <wctype.h>
# include "edition.h"
# include "termcaps.h"
# include "prompt.h"
# include "utils.h"
# include "history.h"
# include "builtins.h"
# include "completion.h"

/*
** Structure globale, comprenant les informations relatives a :
** - l'etat de l'edition de ligne (normal, auto-completion ou historique)
** - l'historique des arguments en ligne de commande
** - l'autocompletion
** - le statut de sortie de la commande precedente (SUCCESS ou Code d'erreur)
*/
typedef struct			s_sh
{
	int				edition_state;
	t_ldl_head		*hist;
	t_ldl			*hist_current;
	t_ldl_head		*history;
	t_ldl			*h_current;
	char			*h_save;
	char			*hist_file;
	int				h_first;
	char			**env;
	unsigned char	exitstatus;
	t_comp			*comp;
	int				comp_status;
}						t_sh;

extern t_sh				g_sh;

# define SIZE_BUF_CMD (128)
# define PROMPT ("✗ ")
#endif
