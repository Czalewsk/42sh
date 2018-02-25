/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:07:30 by maastie           #+#    #+#             */
/*   Updated: 2018/01/11 16:07:31 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		init_closefd(int fds[3])
{
	fds[0] = STDIN_FILENO;
	fds[1] = STDOUT_FILENO;
	fds[2] = STDERR_FILENO;
}

void		reset_fd(int fds[3], t_process *p)
{
	dup2(p->stdin, fds[0]);
	dup2(p->stdout, fds[1]);
	dup2(p->stderr, fds[2]);
}

char		*get_command(char *ret, t_tree *chead)
{
	t_tree	*tmp;

	tmp = chead;
	while (tmp)
	{
		ret = ft_strjoin_free(ft_strjoin_free(ret, tmp->token.str, 0), " ", 0);
		tmp = tmp->right;
	}
	return (ret);
}