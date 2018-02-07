/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_select.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 17:08:42 by bviala            #+#    #+#             */
/*   Updated: 2018/02/07 15:59:07 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	fcmp_select(t_select *s1, t_select *s2)
{
	if (!s1 || !s2)
		return (1);
	return (ft_strcmp(s1->escaped, s2->escaped));
}

t_select	*new_select(char *name)
{
	t_select 	*select;
	struct stat buf;

	select = ft_memalloc(sizeof(t_select));
	select->name = ft_strdup(name);
	select->escaped = escape_it(name);
	select->len = ft_strlen_utf8(select->escaped);
	if (stat(name, &buf) == -1)
	{
	//	exit_status(error) recoder erreur stat
		return (NULL);
	}
	if (S_ISDIR(buf.st_mode))
		select->color += DIR_C;
	if ((S_IXUSR & buf.st_mode) || (S_IXGRP & buf.st_mode) ||
			(S_IXOTH & buf.st_mode))
		select->color += BIN_C;
	if (S_IWOTH & buf.st_mode)
		select->color += WRI_C;
	return (select);
}

void		add_ls(t_comp *comp, t_ldl_head *head, char *search)
{
	DIR				*dir_stream;
	struct dirent	*dir;
	t_ldl			*ldl;
	char			*path;

	int n;
	n = 0;
	path = search ? search : ".\0";
	if (!(dir_stream = opendir(path)))
	{
	//	exit_status(error) recoder erreur opendir
		return ;
	}
	while ((dir = readdir(dir_stream)) != NULL)
	{
		if ((dir->d_name[0] != '.') &&
				(comp->search && !(ft_strncmp(comp->search, dir->d_name,
										ft_strlen_utf8(comp->search)))))
		{
			DEBUG("nb fichiers trouves|%d|\n", ++n);
			ft_ldl_new_node(&ldl, new_select(dir->d_name));
			head = ft_ldl_insert_sort(head, ldl, &fcmp_select);
		}
	}
	closedir(dir_stream);
}
