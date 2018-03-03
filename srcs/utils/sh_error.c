/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 08:05:01 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/03 16:29:33 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char		sh_error_bi(int fd, char ret, int nb, ...)
{
	va_list	ap;
	char	*str;

	if (nb > 0)
	{
		va_start(ap, nb);
		while (nb-- && (str = va_arg(ap, char *)))
			ft_putstr_fd(str, fd);
		va_end(ap);
	}
	return (ret);
}

char		sh_error(char ret, char new_line, void (*f_callback)(), int nb, ...)
{
	va_list	ap;
	char	*str;

	if (f_callback)
		f_callback();
	if (new_line)
		write(2, "\n", 1);
	if (nb)
	{
		va_start(ap, nb);
		ft_putstr_fd("42sh: ", 2);
		g_sh.prompt_display = 0;
		while (nb-- && (str = va_arg(ap, char *)))
			ft_putstr_fd(str, 2);
		va_end(ap);
	}
	return (ret);
}
