/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_folders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 17:50:04 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/16 00:37:36 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

t_list		*glob_folders_get(char *path, char is_relative)
{
	t_list			*folders;
	t_list			*tmp;
	t_glob_files	*folder;
	char			*tmp_path;

	tmp_path = is_relative ? ft_strjoin("./", path) : path;
	folders = ft_list_folders(tmp_path);
	is_relative ? ft_strdel(&tmp_path) : 0;
	tmp = folders;
	while (tmp)
	{
		folder = ft_memalloc(sizeof(t_glob_files));
		folder->path = ft_strjoin(path, tmp->content);
		folder->is_relative = is_relative;
		ft_strdel((char**)&tmp->content);
		tmp->content = folder;
	}
	/* TEST */
	tmp = folders;
	DEBUG("\nFolders :\n");
	while (tmp)
	{
		folder = tmp->content;
		DEBUG("(%s)deep:%d|%s|\n", folder->is_relative ? "./" : "", folder->deep, folder->path);
		tmp = tmp->next;
	}
	/* END TEST */
	return (folders);
}

t_list		*glob_folders_init(t_list *path)
{
	t_glob_process	*elmt;
	t_list			*folders;
	size_t			i;
	t_list			tmp;

	if (!path || !path->next)
		return (NULL);
	elmt = path->content;
	i = (*elmt->path == '/' || (*elmt->path == '.'
				&& *(elmt->path + 1) == '/')) ? 0 : 1;
	path_tmp = ft_strjoin(i ? "./" : "", elmt->path);
	ft_strdel(&path_tmp);
	folders = glob_folders_get(path_tmp, i);
	i = ft_lstlen(path);
	while (--i)
	{
		tmp = 
		ft_lstaddback(&folders, glob_folders())
	}
}

/*
					*/
