/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 21:58:39 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/03 16:29:28 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILS_H
# define __UTILS_H

# include "libft.h"

/* DEFINE ESCAPE */
# define	SH_IS_ESC(str, i) (*(str + i) & 1)
# define	SH_IS_END_DQ(str, i) (*(str + i) & 2)

char		sh_escape(char *str, char **escaped);
char		sh_globbing(char *tkkn, t_list **result);
char		*escape_it(char *str);
char		sh_error(char ret, char new_line, void (*f_callback)(), int nb, ...);
char		sh_error_bi(int fd, char ret, int nb, ...);

#endif
