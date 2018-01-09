/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 16:00:08 by bviala            #+#    #+#             */
/*   Updated: 2017/12/14 14:12:48 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_H
# define OUTPUT_H

# include "libft.h"

void				ft_putendl(char const *s);
void				ft_putnbr(int nb);
void				ft_putchar(char c);
void				ft_putstr(char const *str);
void				ft_putnstr(char const *str, int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_base(int nb, int base);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putnstr_fd(char const *str, int n, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putwchar(wchar_t str);
int					ft_putnwstr(const wchar_t *str, int len);
void				ft_print_wordtab(char **s);
int					ft_putchar_termcap(int c);
void				ft_putnchar(char const c, int n);
void				ft_putnchar_fd(char const c, int n, int fd);

#endif
