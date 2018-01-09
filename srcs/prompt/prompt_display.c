/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:40:07 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/09 16:42:43 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		prompt_display(t_read *info, int new)
{
	new	? write(1, "\n", 1) : 0;
	ft_putstr(PROMPT);
	info->prompt = ft_strlen_utf8(PROMPT);
}
