/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:15:01 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/03 18:49:30 by scorbion         ###   ########.fr       */
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
# include "ast.h"
# include "job_control.h"
# include "parser.h"

/*
** Define :D
*/

# define SIZE_BUF_CMD (128)
# define PROMPT ("Cedychou_sh : ")
// (canard) <U+1F986> A remettre dans le prompt

#endif
