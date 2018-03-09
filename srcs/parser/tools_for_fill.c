/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:07:30 by maastie           #+#    #+#             */
/*   Updated: 2018/03/09 19:45:22 by scorbion         ###   ########.fr       */
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
	close(fds[0]);
	close(fds[1]);
	close(fds[2]);
	dup2(p->stdin, fds[0]);
	dup2(p->stdout, fds[1]);
	dup2(p->stderr, fds[2]);
}

char		*get_command(char *ret, t_tree *chead)
{
	t_tree	*tmp;

	tmp = chead;
	while (tmp->right)
	{
		if (!ret)
			ret = ft_strdup(tmp->token.str);
		else
			ret = ft_strjoin_free(
				ft_strjoin_free(ret, " ", 0), tmp->token.str, 0);
		tmp = tmp->right;
	}
	return (ret);
}

int			clear_execute(char **path, t_process *p)
{
	ft_free_array(path);
	reset_fd(g_sh.fds, p);
	DEBUG("tools_for_fill ligne 53 clear_execute\n exit=%d\n", g_sh.exitstatus);
	ft_free_process(p);
	return (g_sh.exitstatus);
}
