/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_is_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 15:25:09 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/07 17:33:06 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

const static char	g_separator_char[] = "&|;";

char				wrapper_is_arg(t_buf *cmd)
{
	char	*curs;

	if (!g_sh.comp_start)
		return (0);
	curs = cmd->cmd + g_sh.comp_start - 1;
	while (curs > cmd->cmd && ft_isspace(*curs))
		--curs;
	if (ft_strchr(g_separator_char, *curs) && !ft_is_escape(curs, cmd->cmd))
		return (0);
	return (1);
}
