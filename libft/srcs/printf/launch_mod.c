/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 15:05:22 by bviala            #+#    #+#             */
/*   Updated: 2017/06/29 16:14:42 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check_dou(t_temple *temple, va_list ap)
{
	if (temple->conv == 'd' || temple->conv == 'i')
		return (solve_d(temple, ap));
	if (temple->conv == 'D')
	{
		temple->mod = MOD_L;
		return (solve_d(temple, ap));
	}
	if (temple->conv == 'o')
		return (solve_o(temple, ap));
	if (temple->conv == 'O')
	{
		temple->mod = MOD_L;
		return (solve_o(temple, ap));
	}
	if (temple->conv == 'u')
		return (solve_u(temple, ap));
	if (temple->conv == 'U')
	{
		temple->mod = MOD_L;
		return (solve_u(temple, ap));
	}
	else
		return (0);
}

int		check_x(t_temple *temple, va_list ap)
{
	if (temple->conv == 'x')
		return (solve_x(temple, ap));
	if (temple->conv == 'X')
		return (solve_x(temple, ap));
	if (temple->conv == 'p')
	{
		temple->mod = MOD_Z;
		return (solve_p(temple, ap));
	}
	else
		return (0);
}

int		check_sc(t_temple *temple, va_list ap, char *addr_format)
{
	if (temple->conv == 's')
	{
		if (temple->mod & MOD_L)
			return (solve_wstring(temple, ap));
		else
			return (solve_s(temple, ap));
	}
	if (temple->conv == 'S')
		return (solve_wstring(temple, ap));
	if (temple->conv == 'c')
	{
		if (temple->mod & MOD_L)
			return (solve_wchar(temple, ap));
		else
			return (solve_c(temple, ap));
	}
	if (temple->conv == 'C')
		return (solve_wchar(temple, ap));
	if (temple->conv == '%')
		return (print_percent(addr_format, temple));
	else
		return (0);
}
