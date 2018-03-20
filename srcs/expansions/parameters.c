/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:59:37 by thugo             #+#    #+#             */
/*   Updated: 2018/03/19 19:38:07 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "ft_sh.h"

static size_t	lst_contentsize(t_list *lst)
{
	t_list	*cur;
	size_t	size;

	if (!lst)
		return (0);
	cur = lst;
	size = 0;
	while (cur)
	{
		size += cur->content_size;
		cur = cur->next;
	}
	return (size);
}

static char		*substr_join(t_list **substr)
{
	char		*str;
	int			i;
	t_list		*cur;
	t_list		*prev;

	i = 0;
	str = ft_memalloc(lst_contentsize(*substr) + 1);
	cur = *substr;
	while (cur)
	{
		ft_memcpy(str + i, cur->content, cur->content_size);
		i += cur->content_size;
		prev = cur;
		cur = cur->next;
		free(prev->content);
		free(prev);
	}
	*substr = NULL;
	return (str);
}

static void		expand_env(t_list **lst[2], const t_token *tk, char *value,
	char *ifs)
{
	int		i;

	if (tk->id == WORD && ft_strcnt(value, ifs ? ifs : " \t\n"))
	{
		i = -1;
		while (*value && value[++i])
			if (ft_strchr(ifs ? ifs : " \t\n", value[i]))
			{
				if (*(lst[1]) && !i)
					expansions_addtoken(lst[0], substr_join(lst[1]), tk->id);
				else if (!i)
					++value;
				else
				{
					ft_lst_pushend(lst[1], ft_lstnew(value, i));
					expansions_addtoken(lst[0], substr_join(lst[1]), tk->id);
					value += i + 1;
				}
				i = -1;
			}
		if (i > 0)
			ft_lst_pushend(lst[1], ft_lstnew(value, i));
	}
	else
		ft_lst_pushend(lst[1], ft_lstnew(value, ft_strlen(value)));
}

static int		expand_variable(t_list **lst[2], const t_token *tk, char **cur,
	char *found)
{
	int		i;
	char	*name;
	char	*value;

	i = 1;
	while (found[i] && (ft_isalnum(found[i]) || found[i] == '_'))
		++i;
	(i == 1 && found[i] == '?') && i++;
	if (i <= 1)
		return (0);
	if (found - *cur)
		ft_lst_pushend(lst[1], ft_lstnew(*cur, found - *cur));
	name = ft_strncmp("?", found + 1, i - 1) ?
		ft_strndup(found + 1, i - 1) : NULL;
	if ((value = name ? env_get(name) : ft_itoa(g_sh.exitstatus)))
	{
		if (ft_is_escape(found, tk->str))
			ft_lst_pushend(lst[1], ft_lstnew(value, ft_strlen(value)));
		else
			expand_env(lst, tk, value, env_get("IFS"));
	}
	if ((*cur += i) && !name)
		free(value);
	free(name);
	return (1);
}

char			expand_parameters(const t_token *tk, t_list **lst)
{
	t_list	*substr;
	char	*cur;
	int		i;
	int		found;

	i = -1;
	found = 0;
	cur = tk->str;
	substr = NULL;
	while (*cur && cur[++i])
		if (cur[i] == '$' && !(ft_is_escape(cur + i, tk->str) & 221))
			if (expand_variable((t_list **[2]){lst, &substr}, tk, &cur,
					cur + i))
			{
				found = 1;
				cur += i;
				i = -1;
			}
	if (found && i > 0)
		ft_lst_pushend(&substr, ft_lstnew(cur, i));
	if (substr)
		expansions_addtoken(lst, substr_join(&substr), tk->id);
	return (found);
}
