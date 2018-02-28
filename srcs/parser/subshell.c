/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 23:38:08 by maastie           #+#    #+#             */
/*   Updated: 2018/02/27 23:38:08 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

// reussir a lire l info dans le pipe et a la retranscrire en char **; voir en char * et la split;

// char		**how_to_do(char **argv, char *cmd)
// {
// 	int		fd[2];
// 	pid_t 	father;
// 	char	str[2048];

// 	if (pipe(fd) == -1 || (father = fork()) == -1)
// 		return (NULL);
// 	else
// 	{
// 		if (father == 0)
// 		{
// 			dup2(fd[1], STDOUT_FILENO);
// 		// g_sh.exitstatus = parser(&cmd);
// 			close(fd[0]);
// 			exit(parser(&cmd));
// 		}
// 		else
// 		{
// 			waitpid(father, &g_sh.exitstatus, WUNTRACED | WCONTINUED | WNOHANG);
// 			close(fd[1]);
// 			if (g_sh.exitstatus != -1)
// 				while (read(fd[0], str, 2048) > 0)
// 					ft_putstr_fd(str, 1);
// 			// read fd[0] puis add chaque mot en tant qu qrgument;
// 		}
// 	}
// 	if (g_sh.exitstatus != 0)
// 		ft_free_array(argv);
// 	return (argv);
// }

// char	**sub_shell_main(char **argv, char *cmd)
// {
// 	t_tree	*n_head;
// 	t_tree	*n_current;

// 	n_head = NULL;
// 	n_current = NULL;
// 	argv = how_to_do(argv, cmd);
// 	head_tree = n_head;
// 	current = n_current;
// 	return (argv);
// }

// char	*extrac_from_quote(char *dst, char *ref)
// {
// 	int	i;
// 	int	e;

// 	i = 1;
// 	e = 0;
// 	while (ref && ref[i] && ref[i + 1])
// 	{
// 		dst[e] = ref[i++];
// 		e++;
// 	}
// 	dst[e] = '\0';
// 	return (dst);
// }

t_tree	*subshell(t_process *p, t_tree *c)
{
	(void)p;
	// char	*new;
	// t_tree	*save_head_tree;
	// t_tree	*save_current;

	// save_current = current;
	// save_head_tree = head_tree;
	// new = (char *)ft_memalloc(sizeof(char) * ft_strlen(c->token.str));
	// new = extrac_from_quote(new, c->token.str);
	// if (new && new[0] != '\0')
	// 	p->argv = sub_shell_main(p->argv, new);
	// free(new);
	// head_tree = save_head_tree;
	// current = save_current;
	// if (p->argv == NULL)
	// 	return ((void *)1);
	return (c->right);
}