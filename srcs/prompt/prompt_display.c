/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:40:07 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/08 21:11:52 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		prompt_display(t_read *info)
{
	write(1, "\n\r", 2);
	ft_putstr(PROMPT);
	info->prompt = ft_strlen_utf8(PROMPT);
}