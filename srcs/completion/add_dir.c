/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 22:24:41 by bviala            #+#    #+#             */
/*   Updated: 2018/02/08 22:41:27 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		add_dir(t_comp *comp, t_ldl_head *head, char *search)
{
	DIR				*dir_stream;
	struct dirent	*dir;
	t_ldl			*ldl;
	char			*path;

	int n;
	n = 0;
	path = search ? search : ".\0";
	if (!(dir_stream = opendir(".\0")))
	{
	//	exit_status(error) recoder erreur opendir
		return ;
	}
	while ((dir = readdir(dir_stream)) != NULL)
	{
		if ((dir->d_name[0] != '.') && ((!comp->search) ||
				(comp->search && !(ft_strncmp(comp->search, dir->d_name,
										ft_strlen_utf8(comp->search))))))
		{
			DEBUG("nb fichiers trouves|%d|, name |%s|\n", ++n, dir->d_name);
			ft_ldl_new_node(&ldl, new_select(ft_strdup(dir->d_name), search));
			head = ft_ldl_insert_sort(head, ldl, &fcmp_select);
		}
	}
	closedir(dir_stream);
}
