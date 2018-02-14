/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_select.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 17:08:42 by bviala            #+#    #+#             */
/*   Updated: 2018/02/14 14:38:09 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			fcmp_select(t_select *s1, t_select *s2)
{
	if (!s1 || !s2)
		return (1);
	return (ft_strcmp(s1->escaped, s2->escaped));
}

static void	new_select_color(t_select *select, char *name)
{
	struct stat buf;

	if (stat(name, &buf) == -1)
	{
	//	exit_status(error) recoder erreur stat
		select->color = 0;
	}
	if (S_ISDIR(buf.st_mode))
	{
		select->color += DIR_C;
		select->name = ft_strjoin_free(select->name, "/\0", 0);
		select->escaped = ft_strjoin_free(select->escaped, "/\0", 0);
		select->len++;
	}
	if ((S_IXUSR & buf.st_mode) || (S_IXGRP & buf.st_mode) ||
			(S_IXOTH & buf.st_mode))
		select->color += BIN_C;
	if (S_IWOTH & buf.st_mode)
		select->color += WRI_C;
}

t_select	*new_select(char *name, char *path)
{
	t_select	*select;

	select = ft_memalloc(sizeof(t_select));
	select->name = ft_strdup(name);
	select->escaped = escape_it(name);
	select->len = ft_strlen_utf8(select->escaped);
	name = (path) ? ft_strjoin_free(path, name, 1) : name;
	new_select_color(select, name);
	ft_strdel(&name);
	return (select);
}

void		add_ls(t_comp *comp, t_ldl_head *head, char *search)
{
	DIR				*dir_stream;
	struct dirent	*dir;
	t_ldl			*ldl;
	char			*path;

	path = search ? search : ".\0";
	if (!(dir_stream = opendir(path)))
	{
	//	exit_status(error) recoder erreur opendir
		return ;
	}
	while ((dir = readdir(dir_stream)) != NULL)
	{
		if (((dir->d_name[0] != '.') || !ft_strcmp(comp->search, "."))
				&& ((!comp->search) ||
				(comp->search && !(ft_strncmp(comp->search, dir->d_name,
										ft_strlen_utf8(comp->search))))))
		{
			ft_ldl_new_node(&ldl, new_select(ft_strdup(dir->d_name), search));
			head = ft_ldl_insert_sort(head, ldl, &fcmp_select);
		}
	}
	closedir(dir_stream);
}
