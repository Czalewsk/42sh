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

char		*add_it_spaced(char *dst, char *src)
{
	char	*new;

	new = NULL;
	if (!dst)
		dst = ft_strdup(src);
	else
	{
		new = ft_strxjoin(4, dst, " ", src, "\0");
		free(dst);
		return (new);
	}
	return (dst);
}

char		**concat_tab_for_sub(char **argv, char **k, int size)
{
	char	**ret;
	int		i;
	int		a;

	if (!argv)
		return (k);
	i = 0;
	a = 0;
	ret = (char **)ft_memalloc(sizeof(char *) * (size + 2));
	while (argv && argv[i])
	{
			ret[i] = ft_strdup(argv[i]);
			i++;
	}
	i > 1 ? i-- : i;
	while (k && k[a])
	{
		if (ret[i])
			ret[i] = ft_strjoin_free(ret[i], k[a++], 0);
		else
			ret[i] = ft_strdup(k[a++]);
		ret[++i] = NULL;
	}
	ft_free_array(argv);
	ft_free_array(k);
	return (ret);
}

char		**add_to_argv(char **argv, char *to_add)
{
	char	**k;
	int		i;
	int		a;

	i = 0;
	a = 0;
	k = ft_strsplit_whitespaces(to_add);
	while (k && k[i])
		i++;
	while (argv && argv[a])
		a++;
	i = a + i;
	free(to_add);
	return (concat_tab_for_sub(argv, k, i));
}

char		**how_to_do(char **argv, char *cmd)
{
	int		fd[2];
	pid_t 	father;
	char	*sub_out;
	char	*line;

	sub_out = NULL;
	line = NULL;
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
		else
		{
			waitpid(father, &g_sh.exitstatus, WUNTRACED | WCONTINUED);
			close(fd[1]);
		}
		if ((WIFEXITED(g_sh.exitstatus) == 1 && WEXITSTATUS(g_sh.exitstatus) == EXIT_SUCCESS))
		{
			while (get_next_line(fd[0], &line) > 0)
			{
				sub_out = add_it_spaced(sub_out, line);
				ft_strdel(&line);
			}
			ft_strdel(&line);
		}
	}
	return (add_to_argv(argv, sub_out));
}

char	**sub_shell_main(char **argv, char *cmd)
{
	if ((argv = how_to_do(argv, cmd)) == NULL)
		sh_error(0, 0, NULL, 1, "parse error in command substitution");
	return (argv);
}

char	*extrac_from_backtite(char *dst, char *ref)
{
	int	i;
	int	e;

	i = 1;
	e = 0;
	while (ref && ref[i] && ref[i + 1])
	{
		dst[e] = ref[i++];
		e++;
	}
	dst[e++] = '\n';
	dst[e] = '\0';
	return (dst);
}

t_tree	*subshell(t_process *p, t_tree *c)
{
	(void)p;
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
