/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 22:39:56 by bviala            #+#    #+#             */
/*   Updated: 2018/03/29 01:47:58 by thugo            ###   ########.fr       */
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
	char	*num;
	int		ret;

	num = NULL;
	av[0] = "history";
	av[1] = "-d";
	num = ft_itoa(g_sh.history->length);
	av[2] = num;
	av[3] = NULL;
	ret = built_h_clear_one("d", av, p);
	ft_strdel(&num);
	return (ret);
}

static int	built_h_clear_one2(char *str, t_process *p)
{
	size_t		id;

	id = ft_atoi(str);
	if (!id || (id > g_sh.history->length))
	{
		return (sh_error_bi(p->stderr, -1, 3, "builtin history: ",
					str, ": history position out of range\n"));
	}
	ft_ldl_del_id(g_sh.history, g_sh.history->length + 1 - id, &ft_strdel);
	return (EXIT_SUCCESS);
}

int			built_h_clear_one(char *res, char **argv, t_process *p)
{
	int		i;

	if (argv + 2)
		argv = argv + 2;
	else
	{
		return (sh_error_bi(p->stderr, -1, 2, "builtin history: "
		"missing arguments\nusage: history [n]/[-cpds] args\n"));
	}
	if (ft_strchr(res, 'p'))
	{
		i = 0;
		while (argv[i])
			ft_putendl_fd(argv[i++], p->stdout);
		launch_clearlast(p);
	}
	else if (ft_strchr(res, 'd'))
	{
		if (!*argv || built_h_clear_one2(*argv, p) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	update_history(p);
	return (EXIT_SUCCESS);
}

int			built_h_save_one(char **argv, t_process *p)
{
	int		fd;
	char	*cmd;

	launch_clearlast(p);
	argv = argv + 2;
	cmd = ft_strdup(*argv);
	while (++argv && *argv)
		cmd = ft_strjoin_free(ft_strjoin_free(cmd, " \0", 0), *argv, 0);
	g_sh.history = ft_ldl_addfront(g_sh.history, ft_strdup(cmd));
	if (check_history_access(g_sh.hist_file))
	{
		if ((fd = open(g_sh.hist_file, O_RDWR
						| O_APPEND | O_CREAT, 0600)) == -1)
		{
			return (sh_error_bi(p->stderr, -1, 3, "open ",
						g_sh.hist_file, "error\n"));
		}
		ft_putstr_fd("#", fd);
		ft_putendl_fd(cmd, fd);
		close(fd);
	}
	ft_strdel(&cmd);
	return (EXIT_SUCCESS);
}
