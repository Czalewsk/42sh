/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 23:38:08 by maastie           #+#    #+#             */
/*   Updated: 2018/03/19 15:46:38 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char		*read_from_sub(int fd[2], char *sub_out)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd[0], &line) > 0)
	{
		sub_out = add_it_spaced(sub_out, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (sub_out);
}

char		**how_to_do(char **argv, char *cmd)
{
	int		fd[2];
	pid_t	father;
	char	*sub_out;

	sub_out = NULL;
	if (pipe(fd) == -1 || (father = fork()) == -1)
		return (NULL);
	else
	{
		if (father == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			if (parser(&cmd) == -1)
				_exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
		waitpid(father, &g_sh.exitstatus, WUNTRACED | WCONTINUED);
		close(fd[1]);
		if ((WIFEXITED(g_sh.exitstatus) == 1
			&& WEXITSTATUS(g_sh.exitstatus) == EXIT_SUCCESS))
			sub_out = read_from_sub(fd, sub_out);
	}
	return (add_to_argv(argv, sub_out));
}

t_tree		*subshell(t_process *p, t_tree *c)
{
	char	*new;
	t_tree	*save_head_tree;
	t_tree	*save_current;

	save_current = g_current;
	save_head_tree = g_head_tree;
	new = (char *)ft_memalloc(sizeof(char) * ft_strlen(c->token.str));
	new = extrac_from_backtite(new, c->token.str);
	if (new && new[0] != '\n')
		p->argv = sub_shell_main(p->argv, new);
	free(new);
	g_head_tree = save_head_tree;
	g_current = save_current;
	if (p->argv == NULL)
		return ((void *)1);
	return (c->right);
}
