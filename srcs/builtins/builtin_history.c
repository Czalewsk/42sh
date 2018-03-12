/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 19:00:37 by bviala            #+#    #+#             */
/*   Updated: 2018/03/12 17:30:46 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	clear_all(t_process *p)
{
	int		fd;

	ft_ldl_clear(&g_sh.history, &ft_strdel);
	if (check_history_access(g_sh.hist_file))
	{
		if ((fd = open(g_sh.hist_file, O_RDWR | O_TRUNC, 0600)) == -1)
		{
			return (sh_error_bi(p->stderr, -1, 3,
						"open ", g_sh.hist_file, "error\n"));
		}
		close(fd);
	}
	init_history();
	return (EXIT_SUCCESS);
}

static int	display_history(int n, int argc, t_process *p, size_t len)
{
	size_t	len_max;
	t_ldl	*tmp;

	if (!g_sh.history || !argc || !p)
		return (EXIT_FAILURE);
	if (n && (argc > 2))
	{
		return (sh_error_bi(p->stderr, -1, 1,
	"builtin history: too many arguments\nusage: history [n]/[-cdps] args\n"));
	}
	n = n ? n : g_sh.history->length;
	len_max = ft_count_len(g_sh.history->length);
	if (!(tmp = g_sh.history->tail))
		return (EXIT_SUCCESS);
	while (tmp && n--)
	{
		ft_putnchar_fd(' ', len_max - ft_count_len(len), p->stdout);
		ft_putnbr_fd(len, p->stdout);
		ft_putchar_fd(' ', p->stdout);
		ft_putendl_fd(tmp->content, p->stdout);
		tmp = tmp->prev;
		++len;
	}
	return (EXIT_SUCCESS);
}

static int	builtin2(t_process *p, char **argv, char *res)
{
	int		ret;

	ret = -1;
	if (res && (ft_strchr(res, 'c')))
		ret = clear_all(p);
	else if (res && ft_strchr(res, 's'))
		ret = built_h_save_one(argv, p);
	else if (res && (ft_strchr(res, 'd') || ft_strchr(res, 'p')))
		ret = built_h_clear_one(res, argv, p);
	return (ret);
}

int			builtin_history(t_process *p, int argc, char **argv, char **env)
{
	char	*res;
	int		id;
	int		ret;
	int		n;

	(void)env;
	res = NULL;
	if (!(argv[1] && ft_strisnumber(argv[1]) && (n = ft_atoi(argv[1])) > 0))
		n = 0;
	if ((id = ft_getopt(argc, argv, "cdsp", &res)) == -1 && !n)
	{
		ft_putstr_fd("builtin history: -", p->stderr);
		ft_putchar_fd(*res, p->stderr);
		ft_putendl_fd(": illegal option\nusage: history [n]/[-cdps] args"
				, p->stderr);
		ft_strdel(&res);
		return (EXIT_FAILURE);
	}
	if ((n || !*res))
		ret = display_history(n, argc, p, 1);
	else
		ret = builtin2(p, argv, res);
	ft_strdel(&res);
	return (ret);
}
