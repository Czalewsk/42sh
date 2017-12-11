/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 21:58:39 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/10 18:40:35 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILS_H
# define __UTILS_H

# include "libft.h"

/* DEFINE ESCAPE */
# define	SH_IS_ESC(str, i) (*(str + i) & 1)
# define	SH_IS_END_DQ(str, i) (*(str + i) & 2)

char		sh_escape(char *str, char **escaped);
char		**sh_brace_exp(char *tkkn);

#endif