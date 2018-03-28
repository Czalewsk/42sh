/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expoint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 16:30:15 by thugo             #+#    #+#             */
/*   Updated: 2018/03/28 11:26:02 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	make_tokens(t_list **lst, char *expand)
{
	int		ret;
	t_token	token;
	char	*cur;

	cur = expand;
	while ((ret = lexer_getnexttoken(&token, &cur, &expand)) > 0)
	{
		if (token.id != NEWLINE && token.id != HISTORY_EXPOINT)
			expansions_addtoken(lst, token.str, token.id);
		else
			free(token.str);
	}
	free(expand);
	return (ret < 0 ? -1 : 1);
}

static char	*get_exword(char *expoint)
{
	size_t	len;

	len = 0;
	while (expoint[len] && expoint[len] != '"')
		++len;
	return (ft_strndup(expoint, len));
}

static char	*get_fullexpand(const t_token *tk, char *expand, char *expoint,
		char *exword)
{
	char	*fullexpand;

	fullexpand = (char *)ft_memalloc((expoint - tk->str) + ft_strlen(expand) +
			ft_strlen(expoint + ft_strlen(exword)) + 2);
	if (tk->str != expoint)
		ft_strncat(fullexpand, tk->str, (expoint - tk->str));
	ft_strcat(fullexpand, expand);
	ft_strcat(fullexpand, expoint + ft_strlen(exword));
	ft_strcat(fullexpand, "\n");
	ft_putendl_fd(expand, g_sh.fd_tty);
	free(exword);
	free(expand);
	return (fullexpand);
}

/*
**	Le retour est un int comme suivant :
**	(et la nouvelle string est stockee dans expand)
**	-1 : error: event not found;
**	1 : found and change;
**	0 : No need change : exe tel quel;
*/

char		expand_history_expoint(const t_token *tk, t_list **lst)
{
	char	*expoint;
	char	*expand;
	char	*exword;
	int		ret_expoint;

	expoint = tk->str;
	while (*expoint && (expoint = ft_strchr(expoint, '!')) &&
			(ft_is_escape(expoint, tk->str) & ~34))
		++expoint;
	if (!expoint)
		return (sh_error(-1, 0, NULL, 2, tk->str, ": event not found\n"));
	exword = get_exword(expoint);
	if ((ret_expoint = history_expoint(exword, &expand)) < 0)
	{
		sh_error(-1, 0, NULL, 2, exword, ": event not found\n");
		free(exword);
		return (-1);
	}
	else if (!ret_expoint)
	{
		ft_strdel(&exword);
		ft_strdel(&expand);
		return (0);
	}
	return (make_tokens(lst, get_fullexpand(tk, expand, expoint, exword)));
}
