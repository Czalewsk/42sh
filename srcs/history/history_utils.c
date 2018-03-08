/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:26:34 by bviala            #+#    #+#             */
/*   Updated: 2018/03/07 17:24:11 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	history_well_formated(char *line)
{
	int		fd;

	if (!line || line[0] != '#')
	{
		sh_error(0, 1, NULL, 3, RED, "Historique corrompu", C_DEFAULT "\n");
		while ((fd = open(g_sh.hist_file, O_RDWR | O_TRUNC, 0600)) == -1 &&
				errno == EINTR)
			;
		if (fd == -1)
			return (sh_error(0, 1, NULL, 1, "Historique : Open error\n"));
		close(fd);
		get_next_line(-2, NULL);
		return (0);
	}
	return (1);
}

int		check_history_access(const char *file)
{
	struct stat buff;

	errno = 0;
	if (!stat(file, &buff))
	{
		if (S_ISREG(buff.st_mode) && (S_IRUSR & buff.st_mode))
			return (1);
		else
			return (0);
	}
	if (errno == 2)
		return (1);
	return (0);
}

void	init_history(void)
{
	int		fd;
	char	*line;

	g_sh.hist = NULL;
	g_sh.hist_current = NULL;
	g_sh.history = ft_ldl_new_list();
	g_sh.h_current = g_sh.history->head;
	g_sh.h_first = 0;
	g_sh.h_save = NULL;
	line = NULL;
	if (check_history_access(g_sh.hist_file))
	{
		while ((fd = open(g_sh.hist_file, O_RDWR)) == -1 && errno == EINTR)
			;
		if (fd == -1)
			return ;
		while (get_next_line(fd, &line) > 0 && history_well_formated(line))
		{
			g_sh.history = ft_ldl_addfront(g_sh.history, ft_strdup(line));
			ft_strdel(&line);
		}
		ft_strdel(&line);
		close(fd);
	}
}
