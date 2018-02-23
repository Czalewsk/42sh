/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 22:24:41 by bviala            #+#    #+#             */
/*   Updated: 2018/02/16 15:06:34 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		add_dir(t_comp *comp, t_ldl_head *head)
{
	DIR				*dir_stream;
	struct dirent	*dir;
	t_ldl			*ldl;
	int				n;

	n = 0;
	if (!(dir_stream = opendir(".\0")))
		return (sh_error(0, 1, NULL, 1, "Fail opendir\n"));
	while ((dir = readdir(dir_stream)) != NULL)
	{
		if ((dir->d_name[0] != '.') && ft_is_a_dir(dir->d_name) &&
				((!comp->search) ||
				(comp->search && !(ft_strncmp(comp->search, dir->d_name,
										ft_strlen_utf8(comp->search))))))
		{
			++n;
			ft_ldl_new_node(&ldl, new_select(ft_strdup(dir->d_name), NULL));
			head = ft_ldl_insert_sort(head, ldl, &fcmp_select);
		}
	}
	closedir(dir_stream);
	return (n);
}
