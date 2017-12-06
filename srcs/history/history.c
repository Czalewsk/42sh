/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:47:00 by bviala            #+#    #+#             */
/*   Updated: 2017/12/06 14:52:17 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static char	*g_save = NULL;

//		DEBUG LISt
void		ldl_debug_display_list(t_ldl_head *ldl_list)
{
	t_ldl		*ldl;
	size_t			i;

	if (!ldl_list)
	{
		DEBUG("head = NULL\n");
		return ;
	}
	DEBUG("===> list length = |%d| <===\n", ldl_list->length);
	ldl = ldl_list->head;
	DEBUG("check ft_ldl_size= |%d|\n\n", ft_ldl_size(ldl_list));
	i = 1;
	while (ldl)
	{
		DEBUG("position : |%d|, data is |%s|\n", i, ldl->content);
	//	if (i > 1)
//
//			DEBUG("prev is |%s|, ", ldl->prev->content);
//		if (i <	ldl_list->length)
//			DEBUG("next is|%s|\n\n",ldl->next->content);
		ldl = ldl->next;
		i++;
	}
	DEBUG("===>	nodes crossed = |%d| <===\n\n",i- 1);
}

/*
**	A recoder selon $HOME
**		1 = existe et est regulier
**		0 = lien sym ou dir
**		-1 = No such file or directory => need to create
*/
static char	check_history_access(const char *file)
{
	struct stat buff;

	if (!stat(file, &buff))
	{
		if (S_ISREG(buff.st_mode) && (S_IRUSR & buff.st_mode))
			return (1);
		else
			return (0);
	}
	return (-1);
}

static void	ft_close_history(t_ldl_head *list, t_buf *cmd, t_ldl *ldl)
{
	int fd;

	DEBUG("entry close           ");
	if (!(check_history_access(HIST_FILE)) ||
		(fd = open(HIST_FILE, O_RDWR | O_APPEND | O_CREAT, 0700)) == -1)
		return ;
	if (cmd->cmd && (*(cmd->cmd) != '\n'))
	{
		write(fd, cmd->cmd, ft_strlen(cmd->cmd));
		write(fd, "\n", 1);
	}
	close (fd);
	g_save = NULL;
	ldl = NULL;
	list = NULL;
	DEBUG("sortie close          \n");
}

static t_ldl_head	*history_init(t_ldl_head *list)
{
	int			fd;
	int			len_save;
	char		*line;

	line = NULL;
	len_save = ft_strlen(g_save);
	if (!list && !(list = ft_ldl_new_list()))
		ft_error("malloc error", NULL);  // A recoder
	if (check_history_access(HIST_FILE)) // /!\ Coder par rapport a variable $HOME : ~/
	{
		if ((fd = open(HIST_FILE, O_RDWR | O_APPEND | O_CREAT, 0700)) == -1)
		{
			DEBUG("open error history_init\n");
			return (list);
		}
		while (get_next_line(fd, &line) > 0)
			if (!g_save)
				list = ft_ldl_addfront(list, line);
			else
			{
				if (!ft_strncmp(line, g_save, len_save))
					list = ft_ldl_addfront(list, line);
			}
		if (line && (!g_save || (g_save && !ft_strncmp(line, g_save, len_save))))
			list = ft_ldl_addfront(list, line);
		close(fd);
	}
	return (list);	
}

static t_ldl	*ft_display_history(t_buf *cmd, t_ldl_head *list, t_ldl *ldl, t_key *entry)
{
	if (ldl)
	{
		if (entry->entry[2] == 65 && ldl->next)
			ldl = ldl->next;
		else if (entry->entry[2] == 66 && ldl->prev)
			ldl = ldl->prev;
		else if (entry->entry[2] == 53 && list->tail)
			ldl = list->tail;
		else if (entry->entry[2] == 54 && list->head)
			ldl = list->head;
		cmd->cmd = ldl->content;
		DEBUG("content |%s|, cmd |%s|\n", ldl->content, cmd->cmd);
	}
	return (ldl);
}

char	history_mode(t_buf *cmd, t_read *info, t_key *entry)
{
	static t_ldl_head	*list = NULL;
	static int			h = 0;
	static t_ldl		*ldl = NULL;

	(void)info;
	if (!h && entry->entry[2] == 65)
	{
		DEBUG("start history mode\n");
		if (cmd->cmd)
			g_save = cmd->cmd;
		h++;
	}
	if (h && !list)
	{
		if ((list = history_init(list)))
			ldl = list->head;
	}
	if (h && g_save)
	{
		list = ft_ldl_addfront(list, g_save);
	}
	if (entry->entry[0] == 13)
	{
		ft_close_history(list, cmd, ldl);
		h = 0;
	}
	else if (h && entry->entry[0] != 13)
		ldl = ft_display_history(cmd, list, ldl, entry);
	ldl_debug_display_list(list);
	return (0);
}
