/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:43:50 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/28 08:27:03 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PROMPT_H
# define __PROMPT_H

# include "ft_sh.h"

void		prompt_display(t_read *info);
char		prompt_add(char *prompt, char **line);

#endif
