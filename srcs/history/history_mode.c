/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:42:19 by bviala            #+#    #+#             */
/*   Updated: 2017/12/06 15:49:51 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static t_ldl_head	*g_list = NULL;
static t_ldl		*g_ldl = NULL;
static size_t		g_i = 0;

void		close_history(int clear)
{
	int fd;
	int	access;

	g_edition_state = NORMAL;
	if ((access = check_history_access(HIST_FILE)))
	{
		if ((fd = open(HIST_FILE, O_RDWR | O_APPEND | O_CREAT, 0700)) == -1)
			return ;
		write(fd, "\n", 1);
		write(fd, g_ldl->content, ft_strlen(g_ldl->content));
		close(fd);
	}
	if (clear || !access)
	{
		ft_ldl_clear(&g_list, &ft_strdel);
		g_i = 0;
	}
	else
		if (g_i != 1)
		{
			FT_LDL_DEL_FIRST(g_list, &ft_strdel);
			g_i--;
		}
}

char		history_up(t_buf *cmd, t_read *info, t_key *entry)
{
	int	last;

	last =  (entry->entry[2] == 65) ? 0 : 1;
	if (!last)
	{
			g_ldl = g_ldl->next;
			g_i++;
	}
	else
	{
		g_ldl = g_list->tail;
		g_i = g_list->length;
	}
	display_str(cmd, info, g_ldl->content, ft_strlen(g_ldl->content));
	return (0);
}

char		history_do(t_buf *cmd, t_read *info, t_key *entry)
{
	int	first;

	first = (entry->entry[2] == 66) ? 0 : 1;
	if (!first)
	{
			g_ldl = g_ldl->prev;
			g_i++;
	}
	else
	{
		g_ldl = g_list->head;
		g_i = 1;
	}
	display_str(cmd, info, g_ldl->content, ft_strlen(g_ldl->content));
	return (0);
}

static void	history_init(t_buf *cmd, t_read *info)
{
	int		fd;
	size_t	len;
	char	*line;

	line = NULL;
	len = (info->curs_char) ? info->curs_char : ft_strlen(cmd->cmd);
	if (!g_list)
		g_list = ft_ldl_new_list();
	if (check_history_access(HIST_FILE)) // /!\ recoder selon $HOME
	{
		if ((fd = open(HIST_FILE, O_RDWR | O_APPEND | O_CREAT, 0700)) == -1)
		{
			DEBUG("open error history_init\n");
			return ;
		}
		while (get_next_line(fd, &line) > 0)
		{
			if (!info->curs_char)
				g_list = ft_ldl_addfront(g_list, ft_strdup(line));
			else
			{
				if (!ft_strncmp(line, cmd->cmd, len))
					g_list = ft_ldl_addfront(g_list, ft_strdup(line));
			}
			ft_strdel(&line);
		}
		close(fd);
	}
}

char		history_mode(t_buf *cmd, t_read *info, t_key *entry)
{
	g_edition_state = HISTORY;
	if (!g_list)
		history_init(cmd, info);
	if (info->curs_char)
	{
		g_list = ft_ldl_addfront(g_list, ft_strdup(cmd->cmd));
		g_ldl = g_list->head;
		g_i = 1;
	}
	history_up(cmd, info, entry);
	return (0);
}
