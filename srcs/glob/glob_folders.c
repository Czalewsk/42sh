/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_folders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 17:50:04 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/17 19:18:24 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

t_list		*glob_folders_get(char *path, unsigned deep,
		t_list *rules)
{
	t_list			*folders;
	t_list			*tmp;
	t_glob_files	*folder;
	t_list			*next;

	folders = ft_list_folders(path);
	tmp = folders;
	while (tmp)
	{
		next = tmp->next;
		if (!glob_rules_check(tmp->content, rules))
			ft_lst_remove(&folders, tmp, free);
		else
		{
			folder = ft_memalloc(sizeof(t_glob_files));
			folder->path = ft_strjoin(path, tmp->content);
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

char		*glob_is_relative(t_list **path)
{
	char	*ret;
	t_glob_process	*elmt;

	elmt = (*path)->content;
	if (*elmt->path == '/' || (*elmt->path == '.'
				&& *(elmt->path + 1) == '/'))
	{
		ret = ft_strdup(elmt->path);
		ft_lst_remove_index(path, 0, NULL);
	}
	else
		ret = ft_strdup("./");
	return (ret);
}

t_list		*glob_folders_init(t_list *path)
{
	t_list			*folders;
//	size_t			i;
	t_list			*tmp;
	unsigned		deep;

	if (!path || !path->next)
		return (NULL);
	deep = 1;
	glob_folders_get(glob_is_relative(&path), 0,
			((t_glob_process*)(path->content))->rules);
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

