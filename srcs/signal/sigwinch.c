/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigwinch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 14:22:54 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/08 19:24:35 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "sh_signal.h"

void	sigwinch(void)
{
	if (g_sh.edition_state == COMPLETION)
		comp_signal(g_save_cmd, g_save_info);
	else
		update_display();
}
