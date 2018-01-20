/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:31:14 by maastie           #+#    #+#             */
/*   Updated: 2018/01/11 16:31:14 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

// int	modify_fd(int fd, t_tree *c, t_job *job)
// {
// 	if (c->token.id == LESS)
// 	{}
// 	else if (c->token.id == GREAT)
// 	{}
// 	else if (c->token.id == DGREAT)
// 	{}
// 	// if (fd == job->first_process->stdin)
// 	// {}
// 	// else if (fd == job->first_process->stdout)
// 	// {}
// 	// else if (fd == job->first_process->stderr)
// 	// {}
// 	// else
// 	// {}
// }

t_tree	*modify_io(t_tree *clist, t_job *job)
{
	(void)job;
	// int	fd;

	// fd = ft_atoi(clist->token.str);
	// if (fcntl(fd, F_GETFD) == -1)
	// {
	// 	if ((fd = (open(clist->token.str, O_RDWR))) == -1)
	// 	{
	// 		ft_printf("\nError, %s is not set as file descriptor\n", clist->token.str);
	// 		return (clist->right->right->right);
	// 	}
	// }
	// else
	// {
	// 	if (modify_fd(fd, clist->right, job) == -1)
	// 		return ()
	// }
	// // if (ft_strcmp(clist->token.str, "0") == 0)
	// // else if (ft_strcmp(clist->token.str, "1") == 0)
	// // else if (ft_strcmp(clist->token.str, "2") == 0)
	// // reset job->stdERR/OUT/IN avec le list + next + next next
	return (clist->right);
}