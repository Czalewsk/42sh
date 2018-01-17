/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_folders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 17:50:04 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/17 12:49:19 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

t_list		*glob_folders_get(char *path, char is_relative, unsigned deep,
		t_list *rules)
{
	t_list			*folders;
	t_list			*tmp;
	t_glob_files	*folder;
	char			*tmp_path;
	t_list			*next;

	tmp_path = is_relative ? ft_strjoin("./", path) : path;
	folders = ft_list_folders(tmp_path);
	is_relative ? ft_strdel(&tmp_path) : 0;
	tmp = folders;
	while (tmp)
	{
		next = tmp->next;
		if (!glob_rules_check(tmp->content, rules))
		{
			DEBUG("\tDel=%s|", tmp->content);
			ft_lst_remove(&folders, tmp, free);
		}
		else
		{
			DEBUG("\tADD=%s|", tmp->content);
			folder = ft_memalloc(sizeof(t_glob_files));
			folder->path = ft_strjoin(path, tmp->content);
			folder->is_relative = is_relative;
			folder->deep = deep;
			ft_strdel((char**)&tmp->content);
			tmp->content = folder;
		}
		tmp = next;
	}
	/* TEST */
	tmp = folders;
	DEBUG("\nFolders :\n");
	while (tmp)
	{
		folder = tmp->content;
		DEBUG("[%s]\n", folder->path);
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
	t_list			*tmp;
	unsigned		deep;

	if (!path || !path->next)
		return (NULL);
	elmt = path->content;
	deep = 1;
	i = (*elmt->path == '/' || (*elmt->path == '.'
				&& *(elmt->path + 1) == '/')) ? 0 : 1;
	glob_folders_get("", i, 0, elmt->rules);
	(void)folders;
	(void)tmp;
	/*
	i = ft_lstlen(path);
	while (deep < i)
	{
		tmp = folders;
		while (tmp)
		{
			if (deep == ((t_glob_files*)tmp->content)->deep - 1)
				ft_lstaddback(&folders, glob_folders())
		}
		path = path->next;
			deep++;
	}
	*/
	return (NULL);
}

