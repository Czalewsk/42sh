/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:55:15 by bviala            #+#    #+#             */
/*   Updated: 2017/06/29 16:14:55 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		check_modifier(char **buf, t_temple *temple)
{
	temple->mod = 0;
	temple->mod = (!ft_strncmp(*buf, "h", 1)) ?
		MOD_H : temple->mod;
	temple->mod = (!ft_strncmp(*buf, "hh", 2)) ?
		MOD_HH : temple->mod;
	temple->mod = (!ft_strncmp(*buf, "l", 1)) ?
		MOD_L : temple->mod;
	temple->mod = (!ft_strncmp(*buf, "ll", 2)) ?
		MOD_LL : temple->mod;
	temple->mod = (!ft_strncmp(*buf, "j", 1)) ?
		MOD_J : temple->mod;
	temple->mod = (!ft_strncmp(*buf, "z", 1)) ?
		MOD_Z : temple->mod;
	if (temple->mod == MOD_HH || temple->mod == MOD_LL)
		(*buf) += 2;
	else if (temple->mod > 0)
		(*buf)++;
}

void		check_width_prec(char **buf, t_temple *temple)
{
	temple->width = ft_atoi(*buf);
	while (**buf >= '0' && **buf <= '9')
		(*buf)++;
	if (**buf == '.')
	{
		(*buf)++;
		if (**buf >= '1' && **buf <= '9')
			temple->precision = ft_atoi(*buf);
		else
			temple->precision = 0;
		while (**buf >= '0' && **buf <= '9')
			(*buf)++;
	}
	else
		temple->precision = -1;
}

void		check_flag(char **buf, t_temple *temple)
{
	while (ft_isflag(**buf))
	{
		if (**buf == '+' && !(temple->flag & FLAG_PLUS))
			temple->flag += FLAG_PLUS;
		else if (**buf == ' ' && !(temple->flag & FLAG_PLUS)
				&& !(temple->flag & FLAG_ESPACE))
			temple->flag += FLAG_ESPACE;
		else if (**buf == '-' && !(temple->flag & FLAG_MOINS))
			temple->flag += FLAG_MOINS;
		else if (**buf == '#' && !(temple->flag & FLAG_DIESE))
			temple->flag += FLAG_DIESE;
		else if (**buf == '0' && !(temple->flag & FLAG_0))
			temple->flag += FLAG_0;
		(*buf)++;
	}
}

void		init_temple(t_temple *temple)
{
	temple->flag = NO_FLAG;
	temple->width = 0;
	temple->precision = -1;
	temple->mod = NO_MOD;
	temple->conv = 48;
}

void		parsing(char **buf, t_temple *temple)
{
	init_temple(temple);
	check_flag(buf, temple);
	check_width_prec(buf, temple);
	check_modifier(buf, temple);
}
