/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavizet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 14:21:31 by gavizet           #+#    #+#             */
/*   Updated: 2017/12/14 06:57:10 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MATHS_H
# define __MATHS_H

# include "libft.h"

# ifndef HEXA
#  define HEXA "0123456789ABCDEF"
# endif

int					ft_abs(int nb);
int					ft_sqrt(int nb);
int					ft_rec_fac(int nb);
char				*ft_itoa(ssize_t n);
int					ft_atoi(const char *str);
int					ft_pow(int nb, int power);
unsigned int		reverse_bits(unsigned int octet);
char				*ft_itoa_base_uns(uintmax_t nbr, int base);
char				*ft_itoa_base_signed(ssize_t nb, int base);
char				*ft_litoa(long int nbr);
char				*ft_ulitoa(unsigned long int nbr);
char				*ft_llitoa(long long int nbr);
char				*ft_ullitoa(unsigned long long int nbr);
long int			ft_atol(const char *str);

#endif
