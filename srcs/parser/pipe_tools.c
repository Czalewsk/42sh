/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 14:43:53 by maastie           #+#    #+#             */
/*   Updated: 2018/03/13 21:25:38 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void			close_pipe_heredoc(t_tree *c)
{
	int			*fd;
	t_tree		*tmp;

	tmp = c;
	while (tmp)
	{
		if (tmp->token.id == DLESS)
		{
			fd = here_list->content;
			close(fd[1]);
			close(fd[0]);
			ft_lst_remove_index(&here_list, 0, NULL);
			return ;
		}
		if (tmp->token.id == PIPE || tmp->token.id  == AND_IF
				|| tmp->token.id == OR_IF)
			return ;
		tmp = tmp->right;
	}
}

void        test_close_for_heredoc(t_tree *c, int temp[2])
{
    t_tree *tmp;

    tmp = c;
    while (tmp)
    {
            if (tmp->token.id == DLESS)
            {
                    close(temp[0]);
                    return ;
            }
		if (tmp->token.id == PIPE || tmp->token.id  == AND_IF
				|| tmp->token.id == OR_IF)
                    return ;
            tmp = tmp->right;
    }
}

void			wait_multiple_proc(t_list *pid_list)
{
	while (pid_list)
	{
		if (waitpid(*(pid_t*)pid_list->content,
					&g_current_process->returned, 0) == -1)
			DEBUG("Erreur waitpid %s| 2\n", strerror(errno)) //utiliser sh_error
				pid_list = pid_list->next;
	}
}

pid_t			init_pipe_run(pid_t f, int p[2][2], t_tree *c, t_tree *e)
{
	close(p[1][1]);
	if (c != e && pipe(p[0]) == -1)
		return (-1);         // MSG d'erreur
	test_close_for_heredoc(c, p[1]);
	p[1][1] = p[0][1];
	if ((f = fork()) == -1)
		return (-1);        // MSG d'erreur	
	return (f);
}

void			dup_and_close_son_pipe(t_tree *c, t_tree *e, int p[2][2], t_list *pid_list)
{
	if (c != e)
		dup_and_close(p[1][1], STDOUT_FILENO, p[0][0]);
	if (pid_list)
		dup_and_close(p[1][0], STDIN_FILENO, p[0][1]);
}
