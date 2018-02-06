/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:59:37 by thugo             #+#    #+#             */
/*   Updated: 2018/02/06 15:54:30 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "ft_sh.h"

/* OLD VERSION V1 */
/*t_list	*expand_parameters(t_token *tk)
{
	t_list	*lst[2];
	t_token	newtk;
	char	**splitval;
	char	*val[2];
	int		i;

	lst[0] = NULL;
	if (tk->id != PARAM_EXP || !(val[0] = ft_getenv(g_sh.env, tk->str + 1)))
		return (NULL);
	val[1] = ft_getenv(g_sh.env, "IFS");
	if (!(splitval = ft_strsplits(val[0], val[1] ? val[1] : " \t\n")))
		return (NULL);
	i = -1;
	newtk.id = WORD;
	while (splitval[++i])
	{
		newtk.str = splitval[i];
		newtk.size = ft_strlen(newtk.str);
		if (!(lst[1] = ft_lstnew(&newtk, sizeof(t_token))))
			exit(EXIT_FAILURE);
		ft_lst_pushend(&lst[0], lst[1]);
	}
	free(splitval);
	return (lst[0]);
*/

/* OLD VERSION V2 */
/*static int	next_expand(t_token *tk, t_token *newtk, char **cur)
{
	int		i;
	char	*val;
	char	*name;
ft_printf("\nEnter next_expand");
	i = 0;
	while ((*cur)[i])
	{
		if ((*cur)[i] == '$' && !ft_is_escape(*cur + i, tk->str))
		{
			if (i && !newtk->str)
				newtk->str = ft_strndup(*cur, i); // Protect
			else if (i && newtk->str)
				newtk->str = ft_strjoin_free(newtk->str, ft_strndup(*cur, i), 2);// Protec
			*cur += i;
			i = 0;
			while (*cur + i && (ft_isalnum((*cur)[i]) || (*cur)[i] == '_'))
				++i;
			if (i > 1)
			{
				if (!(name = ft_strndup(*cur, i)))
					exit(EXIT_FAILURE);
				if ((val = ft_getenv(g_sh.env, name)))
					newtk->str = ft_strjoin_free(newtk->str, val, 0); // Prot
				else
					newtk->str = ft_strjoin_free(newtk->str, ft_strndup(*cur, i), 2); // Protect
				free(name);
				*cur += i;
				i = 0;
			}
		}
		++i;
	}
	if (newtk->str)
		return (1);
	return (0);
}

t_list		*expand_parameters(t_token *tk)
{
	t_list	*lst;
	t_list	*new;
	t_token	newtk;
	char	*cur;

	if (tk->id != WORD && tk->id != ASSIGNMENT_WORD)
		return (NULL);
	lst = NULL;
	cur = tk->str;
	newtk.str = NULL;
	while (next_expand(tk, &newtk, &cur))
	{
		newtk.size = ft_strlen(newtk.str);
		if (!(new = ft_lstnew(&newtk, sizeof(t_token))))
			exit(EXIT_FAILURE);
		ft_lst_pushend(&lst, new);
		ft_bzero(&newtk, sizeof(t_token));
	}
	return (lst);
}*/

static void	save_token(t_list **lst, char *str, size_t size, size_t *tlen)
{
	t_list	*el;
	setbuf(stdout, NULL);
	printf("\nSaveToken: %.*s", (int)size, str);
	if (!(el = ft_lstnew(str, size)))
		exit(EXIT_FAILURE);
	ft_lst_pushend(lst, el);
	*tlen += size;
}

static char	*join_tokens(t_list **lst, size_t tlen)
{
	int		i;
	char	*join;
	t_list	*cur;
	t_list	*next;

	if (!lst || !tlen)
		return (NULL);
	cur = *lst;
	join = ft_memalloc(tlen + 1);
	i = 0;
	while (cur)
	{
		ft_memcpy(join + i, cur->content, cur->content_size);
		i += cur->content_size;
		next = cur->next;
		free(cur->content);
		free(cur);
		cur = next;
	}
	*lst = NULL;
	return (join);
}

/*static int	next_expand(t_token *tk, t_token *newtk,  char **cur)
{
	int		i;
	int		u;
	char	*val;
	char	*name;
	t_list	*lst;
	size_t	tlen;
	int		found;

	lst = NULL;
	newtk->str = NULL;
	i = 0;
	found = 0;
	tlen = 0;
	while ((*cur)[i])
	{
		if ((*cur)[i] == '$' && !ft_is_escape(*cur + i, tk->str))
		{
			u = 1;
			while ((*cur)[i + u] && (ft_isalnum((*cur)[i + u]) ||
					(*cur)[i + u] == '_'))
				++u;
			if (u > 1)
			{
				++found;
				if (i)
					save_token(&lst, *cur, i, &tlen);
				if (!(name = ft_strndup(*cur + i + 1, u - 1)))
					exit(EXIT_FAILURE);
				if ((val = ft_getenv(g_sh.env, name)))
					save_token(&lst, val, ft_strlen(val), &tlen);
				free(name);
				*cur += i + u;
				i = -1;
			}
		}
		++i;
	}
	if (i && found)
		save_token(&lst, *cur, i, &tlen);
	if (found && lst)
	{
		newtk->str = join_tokens(&lst, tlen);
		newtk->size = tlen;
	}
	else if (found)
	{
		newtk->str = ft_strdup("");
		newtk->size = 0;
	}
	*cur += i;
	if (newtk->str)
		return (1);
	return (0);
}*/

/*t_list		*expand_parameters(t_token *tk)
{
	t_list	*lst;
	t_list	*el;
	t_token	newtk;
	char	*cur;

	if (tk->id != WORD && tk->id != ASSIGNMENT_WORD)
		return (NULL);
	lst = NULL;
	newtk.id = tk->id;
	cur = tk->str;
	while (next_expand(tk, &lst, &cur))
	{
		if (!(el = ft_lstnew(&newtk, sizeof(t_token))))
			exit(EXIT_FAILURE);
		ft_lst_pushend(&lst, el);
	}
	return (lst);
}*/

t_list			*expand_parameters(t_token *tk)
{
	t_list	*lst;
	t_list	*mainlst;
	t_token newtk;
	int		i;
	int		u;
	int		x;
	char	*val;
	char	*name;
	char	*cur;
	char	*ifs;
	char	esc;
	size_t	tlen;
	int		found;

	if (tk->id != WORD && tk->id != ASSIGNMENT_WORD)
		return (NULL);
	lst = NULL;
	mainlst = NULL;
	newtk.str = NULL;
	newtk.id = tk->id;
	cur = tk->str;
	ifs = ft_getenv(g_sh.env, "IFS");
	i = 0;
	found = 0;
	tlen = 0;
	while (cur[i])
	{
		if (cur[i] == '$' && ((esc = ft_is_escape(cur + i, tk->str)) == '"' ||
			!esc))
		{
			u = 1;
			while (cur[i + u] && (ft_isalnum(cur[i + u]) || cur[i + u] == '_'))
				++u;
			if (u > 1)
			{
				++found;
				if (i)
					save_token(&lst, cur, i, &tlen);
				name = ft_strndup(cur + i + 1, u - 1);
				if ((val = ft_getenv(g_sh.env, name)))
				{
					if (tk->id == WORD && ft_strcnt(val, ifs ? ifs : " \t\n"))
					{
						x = 0;
						while (val[x])
						{
							if (ft_strchr(ifs ? ifs : " \t\n", val[x]))
							{
								if (tlen && !x)
								{
									newtk.str = join_tokens(&lst, tlen);
									newtk.size = tlen;
									ft_lst_pushend(&mainlst, ft_lstnew(&newtk,
										sizeof(t_token)));
									newtk.str = NULL;
									tlen = 0;
								}
								else if (!x)
									++val;
								else
								{
									save_token(&lst, val, x, &tlen);
									newtk.str = join_tokens(&lst, tlen);
									newtk.size = tlen;
									ft_lst_pushend(&mainlst, ft_lstnew(&newtk,
										sizeof(t_token)));
									newtk.str = NULL;
									tlen = 0;
									val += x + 1;
								}
								x = -1;
							}
							++x;
						}
						if (x)
							save_token(&lst, val, x, &tlen);
					}
					else
						save_token(&lst, val, ft_strlen(val), &tlen);
				}
				free(name);
				cur += i + u;
				i = -1;
			}
		}
		++i;
	}
	if (i && found)
		save_token(&lst, cur, i, &tlen);
	if (found && lst)
	{
		newtk.str = join_tokens(&lst, tlen);
		newtk.size = tlen;
	}
	else if (found && !mainlst)
	{
		newtk.str = ft_strdup("");
		newtk.size = 0;
	}
	if (newtk.str)
		ft_lst_pushend(&mainlst, ft_lstnew(&newtk, sizeof(t_token)));
	return (mainlst);
}
