/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:47:00 by bviala            #+#    #+#             */
/*   Updated: 2017/11/21 18:46:26 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

//		DEBUG LISt
void	ldl_debug_display_list(t_ldl_head *ldl_list)
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

static t_ldl_head	*history_init(t_ldl_head *list)
{
	int			fd;
	char		*line;

	line = NULL;
	if (!list && !(list = ft_ldl_new_list()))
		ft_error("malloc error", NULL);  // A recoder
	if (check_history_access(HIST_FILE) > 0) // /!\ Coder par rapport a variale $HOME : ~/
	{
		if ((fd = open(HIST_FILE, O_RDONLY)) == -1)
			return (list);
		while (get_next_line(fd, &line) > 0)
			list = ft_ldl_addfront(list, line);
		if (line)
			list = ft_ldl_addfront(list, line);
		close(fd);
	}
	return (list);	
}

char	history_mode(t_buf *cmd, t_read *info, t_key *entry)
{
	static int			h = 0;
	static t_ldl_head	*list = NULL;

	if (!list)
		list = history_init(list);
	if (!h)
		h++;
//	ldl_debug_display_list(list);
	(void)cmd;
	(void)info;
	(void)entry;
	return (0);
}
