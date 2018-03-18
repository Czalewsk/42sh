/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_sigcont.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 18:48:31 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/18 19:50:39 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	signal_sigcont(void)
{
	while (tcgetpgrp(g_shell_terminal) != g_shell_pgid)
		kill(-g_shell_pgid, SIGTTIN);
	termcaps_set_tty();
}
