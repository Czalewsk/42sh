/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 08:05:01 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/13 18:27:00 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char		sh_error(char *msg, char ret, void *f_callback())
{
	if (msg)
	{
		g_sh.prompt_display = 0;
		write(2, "\n", 1);
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(msg, 2);
	}
	if (f_callback)
		f_callback();
	return (ret);
}
