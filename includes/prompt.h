/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:43:50 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/11 00:38:24 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PROMPT_H
# define __PROMPT_H

# include "ft_sh.h"

void		prompt_display(t_read *info, int new);
char		prompt_add(char *prompt, char **line, int i);
int			sh_prompt_git(void);
#endif
