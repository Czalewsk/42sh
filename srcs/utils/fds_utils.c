/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 19:20:42 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/05 19:23:14 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

inline void	sh_savefds(int savefds[3])
{
	savefds[0] = dup(STDIN_FILENO);
	savefds[1] = dup(STDOUT_FILENO);
	savefds[2] = dup(STDERR_FILENO);
}

inline void	sh_restorefds(int savefds[3])
{
	dup2(savefds[0], STDIN_FILENO);
	dup2(savefds[1], STDOUT_FILENO);
	dup2(savefds[2], STDERR_FILENO);
}
