/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 07:19:33 by thugo             #+#    #+#             */
/*   Updated: 2018/02/23 01:36:25 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <pwd.h>
#include "expansions.h"
#include "ft_sh.h"

static t_list	*tilde_parameters(const t_token *tk, char **expand)
{
	t_list	*lstparam;
	t_list	*prev;
	t_token	ptk;

	lstparam = NULL;
	ptk.str = *expand;
	ptk.size = ft_strlen(ptk.str);
	ptk.id = tk->id;
	if (expand_parameters(&ptk, &lstparam) && lstparam)
	{
		free(*expand);
		*expand = ((t_token *)lstparam->content)->str;
		prev = lstparam;
		lstparam = lstparam->next;
		free((t_token *)prev->content);
		free(prev);
	}
	return (lstparam);
}

static char		*tilde_concat(const t_token *tk, char *expand, int loginsize,
	char *tilde)
{
	char	*fullstr;
	size_t	index;

	fullstr = (char *)ft_memalloc(tk->size + ft_strlen(expand));
	ft_strncpy(fullstr, tk->str, (index = tilde - tk->str));
	ft_strcpy(fullstr + index, expand);
	ft_strcpy(fullstr + index + ft_strlen(expand), tilde + loginsize + 1);
	return (fullstr);
}

static char		*tilde_getlogindir(char *tilde, int loginsize)
{
	char			*dir;
	char			backup;
	struct passwd	*pwd;

	dir = NULL;
	backup = '\0';
	ft_swap((void **)&backup, (void **)(tilde + loginsize + 1));
	if ((pwd = getpwnam(tilde + 1)))
		dir = pwd->pw_dir;
	ft_swap((void **)&backup, (void **)(tilde + loginsize + 1));
	return (dir);
}

char			expand_tilde(const t_token *tk, t_list **lst)
{
	char	*tilde;
	int		loginsize;
	char	*expandstr;
	t_list	*lstparam;

	if (!(tilde = tk->id == ASSIGNMENT_WORD ?
			ft_strchr(tk->str, '=') : tk->str))
		return (0);
	if ((tk->id == ASSIGNMENT_WORD && *(++tilde) != '~') || *tilde != '~')
		return (0);
	loginsize = 0;
	while (tilde[loginsize + 1] && tilde[loginsize + 1] != '/')
		++loginsize;
	expandstr = loginsize ? tilde_getlogindir(tilde, loginsize) :
		ft_getenv(g_sh.env, "HOME");
	if (expandstr)
	{
		expandstr = tilde_concat(tk, expandstr, loginsize, tilde);
		lstparam = tilde_parameters(tk, &expandstr);
		expansions_addtoken(lst, expandstr, tk->id);
		if (lstparam)
			ft_lstadd(lst, lstparam, 0);
	}
	return (expandstr ? 1 : 0);
}
