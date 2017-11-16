/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 17:52:43 by bviala            #+#    #+#             */
/*   Updated: 2017/08/17 10:23:36 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

# define NO_FLAG 0
# define FLAG_DIESE 1
# define FLAG_0 2
# define FLAG_MOINS 4
# define FLAG_PLUS 8
# define FLAG_ESPACE 16

# define NO_MOD 0
# define MOD_H 1
# define MOD_HH 2
# define MOD_L 4
# define MOD_LL 8
# define MOD_J 16
# define MOD_Z 32

typedef struct		s_temple
{
	int		flag;
	int		width;
	int		precision;
	int		mod;
	char	*str;
	char	conv;
}					t_temple;

int					ft_printf(const char *restrict format, ...);
void				ft_putwchar(wchar_t c);

/*
** parser
*/
int					ft_isflag(char c);
int					ft_isaconv(char c);
void				parsing(char **buf, t_temple *temple);

/*
** fonctions check
*/
int					check_dou(t_temple *temple, va_list ap);
int					check_sc(t_temple *temple, va_list ap, char *adrr_format);
int					check_x(t_temple *temple, va_list ap);

/*
** fonctions d'affichage
*/
int					print_blank(t_temple *temple);
int					print_hexa(t_temple *temple);
int					print_zero(t_temple *temple);
int					print_preci(char *str, t_temple *temple);
int					print_wsign(char *str, t_temple *temple);
int					print_percent(char *str, t_temple *temple);

/*
** conversions mod
*/
char				*conv_sin(t_temple *temple, va_list ap);
char				*conv_unsin(t_temple *temple, va_list ap, int base);

/*
** solve
*/
int					solve_c(t_temple *temple, va_list ap);
int					solve_d(t_temple *temple, va_list ap);
int					solve_o(t_temple *temple, va_list ap);
int					solve_p(t_temple *temple, va_list ap);
int					solve_s(t_temple *temple, va_list ap);
int					solve_u(t_temple *temple, va_list ap);
int					solve_wchar(t_temple *temple, va_list ap);
int					solve_wstring(t_temple *temple, va_list ap);
int					solve_x(t_temple *temple, va_list ap);

#endif
