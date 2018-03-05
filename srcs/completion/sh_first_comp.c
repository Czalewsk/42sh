/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_first_comp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 12:27:23 by bviala            #+#    #+#             */
/*   Updated: 2018/03/05 23:43:51 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	comp_file(char *to_search, char *tmp, size_t len)
{
	if (!*to_search)
		g_sh.comp->search = NULL;
	else if (ft_is_a_dir(to_search) && ft_strcmp(to_search, ".\0"))
	{
		len = ft_strlen(to_search);
		if (to_search[len - 1] == '/')
			g_sh.comp->path = ft_strdup(to_search);
		else
			g_sh.comp->path = ft_strjoin(to_search, "/\0");
		g_sh.comp->search = NULL;
	}
	else
	{
		tmp = to_search;
		if (ft_strchr(tmp, '/'))
		{
			tmp = to_search;
			while (tmp && ft_strchr(tmp, '/'))
				tmp = ft_strchr(tmp, '/') + 1;
			g_sh.comp->path = ft_strndup(to_search,
					ft_strlen_utf8(to_search) - ft_strlen_utf8(tmp));
		}
		g_sh.comp->search = ft_strdup(tmp);
	}
	add_ls(g_sh.comp, g_sh.comp->head, g_sh.comp->path);
}

static void	comp_all(char *to_search)
{
	int ret;

	ret = 0;
	if (!*to_search)
		g_sh.comp->search = NULL;
	else
		g_sh.comp->search = ft_strdup(to_search);
	ret += add_bin(g_sh.comp, g_sh.comp->head);
	ret += add_env(g_sh.comp, g_sh.comp->head, g_sh.env);
	if (ret)
		ret += add_dir(g_sh.comp, g_sh.comp->head);
	else
	{
		ft_strdel(&g_sh.comp->search);
		comp_file(to_search, to_search, ft_strlen(to_search));
	}
}

char		first_comp(t_buf *cmd, t_read *info, t_key *entry, char *to_search)
{
	t_ldl *ldl;

	g_sh.edition_state = COMPLETION;
	g_sh.comp = ft_memalloc(sizeof(t_comp));
	comp_termcaps_set_tty(0);
	g_sh.comp->head = ft_ldl_new_list();
	if (!g_sh.comp_status)
		comp_all(to_search);
	else
		comp_file(to_search, to_search, ft_strlen(to_search));
	ldl = g_sh.comp->head ? g_sh.comp->head->head : NULL;
	if (ldl)
		((t_select *)ldl->content)->is_current = 1;
	else
		return (quit_completion(cmd, info, entry));
	return (sh_comp(cmd, info, entry));
}
