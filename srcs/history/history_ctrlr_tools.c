/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_ctrlr_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:54:00 by bviala            #+#    #+#             */
/*   Updated: 2018/01/10 16:54:27 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	ft_clear_prompt(t_read *info, int first, size_t pos, char *new)
{
	cursor_back_begin(info);
	if (first)
	{
		info->prompt = 22 + pos;
		info->curs_char = new ? ft_strlen_utf8(new) : 0;
	}
}
