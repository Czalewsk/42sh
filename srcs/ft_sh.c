/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:10:34 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/06 17:52:13 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	termcaps_init(env);
	termcaps_restore_tty();
}