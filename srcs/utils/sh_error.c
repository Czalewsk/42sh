/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 08:05:01 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/13 08:38:16 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char		sh_error(char *msg, char ret, void *f_callback())
{
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		write(2, "\n", 1);
	}
	if (f_callback)
		f_callback();
	return (ret);
}
