/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expoint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 21:15:11 by bviala            #+#    #+#             */
/*   Updated: 2018/03/14 18:01:22 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static char	*change_expoint_h(char *str, char *old, char *new)
{
	size_t	len;
	char	*s;
	char	*curs;


	len = ft_strlen(str) - ft_strlen(old) + ft_strlen(new);
	s = (char *)ft_memalloc(len);
	curs = ft_strstr(str, old);
	s = ft_strncpy(s, str, len - ft_strlen(curs));
	s = ft_strcat(s, new);
	s = ft_strcat(s, curs + ft_strlen(old));
	return (s);
}

static char	*expoint_contain(char *str)
{
	char	*new;
	t_ldl	*ldl;

	new = NULL;
	ldl = g_sh.history->head;
	while (ldl && !ft_strstr(ldl->content, str))
		ldl = ldl->next;
	if (ldl)
		new = ft_strdup(ldl->content);
	return (new);
}

static char	*expoint_start(char *str)
{
	char	*new;
	size_t	len;
	t_ldl	*ldl;

	new = NULL;
	len = ft_strlen(str);
	ldl = g_sh.history->head;
	while (ldl && ft_strncmp(str, ldl->content, len))
		ldl = ldl->next;
	if (ldl)
		new = ft_strdup(ldl->content);
	return (new);
}

static char	*expoint_isnumber(char *str)
{
	char	*new;
	t_ldl	*ldl;
	int		nb;

	new = NULL;
	if (!(nb = ft_atoi(str)))
		return (NULL);
	if (nb > 0)
	{
		ldl = g_sh.history->tail;
		while (ldl && --nb > 0)
			ldl = ldl->prev;
	}
	else
	{
		ldl = g_sh.history->head;
		while (ldl && ++nb < 0)
			ldl = ldl->next;
	}
	if (ldl)
		new = ft_strdup(ldl->content);
	return (new);
}

char		*history_expoint(char *str)
{
	char	*new;
	char	*save;

	new = NULL;
	if (!str || str[0] != '!' || !g_sh.history || !g_sh.history->head)
		return (NULL);
	else if (str[1] && str[1] == '!' && g_sh.history->head->next)
		new = ft_strdup(g_sh.history->head->next->content);
	else if (ft_strisnumber(str + 1))
		new = expoint_isnumber(str + 1);
	else if (str[1] && (str[1] == '?'))
		new = expoint_contain(str + 2);
	else if (str[1])
		new = expoint_start(str + 1);
	if (new)
	{
		save = change_expoint_h(g_sh.history->head->content, str, new);
		FT_LDL_DEL_FIRST(g_sh.history, &ft_strdel);
		g_sh.history = ft_ldl_addfront(g_sh.history, save);
	}
	return (new);
}
