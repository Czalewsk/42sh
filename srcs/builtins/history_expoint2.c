/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expoint2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:00:01 by bviala            #+#    #+#             */
/*   Updated: 2018/03/29 13:58:52 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		built_h_error_s(t_process *p)
{
	return (sh_error_bi(p->stderr, -1, 2, "builtin history: ",
		"missing arguments\nusage : history -s args\n"));
}

char	*built_h_isas(char **argv, t_process *p)
{
	launch_clearlast(p);
	argv = argv + 2;
	if (!*argv)
		return (NULL);
	else
		return (ft_strdup(*argv));
}

int		built_h_isad(char **argv, t_process *p)
{
	if (!*argv)
	{
		return (sh_error_bi(p->stderr, -1, 2, "builtin history: ",
			"missing arguments\nusage : history -d args\n"));
	}
	if (built_h_clear_one2(*argv, p) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	update_history(p);
	return (EXIT_SUCCESS);
}

void	update_expoint_h(t_ldl_head *history, char *save)
{
	t_ldl	*ldl;
	int		fd;

	if (!history)
		return ;
	g_sh.history = ft_ldl_addfront(history, save);
	if (check_history_access(g_sh.hist_file))
	{
		if ((fd = open(g_sh.hist_file,
						O_WRONLY | O_TRUNC | O_CREAT, 0600)) == -1)
		{
			sh_error_bi(2, 0, 3, "open ", g_sh.hist_file, "error\n");
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

char	*change_expoint_h(char *str, char *old, char *new)
{
	size_t	len;
	char	*s;
	char	*curs;

	len = ft_strlen(str) - ft_strlen(old) + ft_strlen(new);
	s = (char *)ft_memalloc(len + 1);
	curs = ft_strstr(str, old);
	s = ft_strncpy(s, str, ft_strlen(str) - ft_strlen(curs));
	s = ft_strcat(s, new);
	s = ft_strcat(s, curs + ft_strlen(old));
	ft_strdel(&str);
	return (s);
}
