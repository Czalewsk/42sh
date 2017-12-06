/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_escape.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 21:41:31 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/06 16:48:07 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SH_ESCAPE_H
# define __SH_ESCAPE_H

# include "libft.h"

extern unsigned int		g_nb_remove;

void			*sh_esc_squote(char *str, char *escaped, char *to_remove,
		int index);
void			*sh_esc_bslash(char *str, char *escaped, char *to_remove,
		int index);
void			set_escape(char *str, unsigned int index, char bit);
void			*sh_esc_dquote(char *str, char *escaped, char *to_remove,
		int index);
char		sh_is_escape(char *str, unsigned int index);
void		set_remove(char *str, unsigned int index);
void			*escape_fonctions(char *str, char *escaped, char *to_remove,
		int index);

#endif
