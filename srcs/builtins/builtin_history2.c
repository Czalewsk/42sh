/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 22:39:56 by bviala            #+#    #+#             */
/*   Updated: 2018/03/10 00:24:51 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	update_history(t_process *p)
{
	t_ldl	*ldl;
	int		fd;
	
	if (!g_sh.history)
		return ;
	if (check_history_access(g_sh.hist_file))
	{
		if ((fd = open(g_sh.hist_file, O_RDWR
						| O_TRUNC, 0600)) == -1)
		{
			sh_error_bi(p->stderr, 0, 3, "open ", g_sh.hist_file, "error\n");
			return ;
		}
		ldl = g_sh.history->tail;
		while (ldl)
		{
			ft_putstr_fd("#", fd);
			ft_putendl_fd(ldl->content, fd);
			ldl = ldl->prev;
		}
		close(fd);
	}
}

static int	launch_clearlast(t_process *p)
{
	char	*av[4];

	av[0] = "history";
	av[1] = "-d";
	av[2] = "1";
	av[3] = NULL;
	return (built_h_clear_one("d", av, p));
}

int			built_h_clear_one(char *res, char **argv, t_process *p)
{
	int		i;
	size_t	id;

	if (argv + 2)
		argv = argv + 2;
	else
		return (sh_error_bi(p->stderr, -1, 1,
	"builtin history: missing arguments\nusage: history [n]/[-cpds] args\n"));
	if (ft_strchr(res, 'p'))
	{
		i = 0;
		while (argv[i])
			ft_putendl_fd(argv[i++], p->stdout);
		launch_clearlast(p);
	}
	else if (ft_strchr(res, 'd'))
	{
		id = ft_atoi(*argv);
		if (!id || (id > g_sh.history->length))
			return (sh_error_bi(p->stderr, -1, 3,
		"builtin history: ", *argv, ": history position out of range\n"));
		ft_ldl_del_id(g_sh.history, id, &ft_strdel);
	}
	update_history(p);
	return (EXIT_SUCCESS);
}

int			built_h_save_one(char **argv, t_process *p)
{
	int 	fd;
	char	*cmd;

	launch_clearlast(p);
	argv = argv + 2;
	cmd = ft_strdup(*argv);
	while (++argv && *argv)
	{
		cmd = ft_strjoin_free(cmd, " \0", 0);
		cmd = ft_strjoin_free(cmd, *argv, 0);
	}
	g_sh.history = ft_ldl_addfront(g_sh.history, ft_strdup(cmd));
	if (check_history_access(g_sh.hist_file))
	{
		if ((fd = open(g_sh.hist_file, O_RDWR
						| O_APPEND | O_CREAT, 0600)) == -1 )
			return (sh_error_bi(p->stderr, -1, 3, "open ",
						g_sh.hist_file, "error\n"));
		ft_putstr_fd("#", fd);
		ft_putendl_fd(cmd, fd);
		close(fd);
	}
	ft_strdel(&cmd);
	return (EXIT_SUCCESS);
}
