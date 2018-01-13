/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_rules_square.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 07:12:47 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/13 19:28:31 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

const char	g_special_char[] = "|&;<>()$`\\\"' \t\n";

char	*square_find_end(char *curs)
{
	char	*end;

	end = NULL;
	if (*curs == '^')
		curs++;
	if (*curs == ']')
		curs++;
	while (*curs && !end)
	{
		if (*curs == '\\')
			curs += *(curs + 1) ? 2 : 1;
		if (*curs == ']')
			end = curs;
		else if (ft_strchr(g_special_char, *curs))
			return (NULL);
	}
	return (end);
}

static	char	rules_square_range(char **curs, char *end,
		char (*matching)[255])
{
	char	start_pttrn;
	char	end_pttrn;

	if ((end - *curs) < 3)
		return (0);
	if (**curs == '\\')
		(*curs)++;
	start_pttrn = **curs;
	if (**curs != '-')
		return (0);
	if (**curs == '\\')
	{
		if ((*curs) + 1 < end)
			(*curs)++;
		else
			return (0);
	}
	end_pttrn = **curs;
	if (start_pttrn > end_pttrn)
		return (0);
	while (start_pttrn <= end_pttrn)
		(*matching)[(int)start_pttrn++] = 1;
	return (1);
}

static	void	rules_square_char(char **curs, char *end,
		char (*matching)[255])
{
	if (**curs == '\\' && (*curs) + 1 < end)
		(*curs)++;
	(*matching)[(int)**curs] = 1;
}

static	void	check_first_char(char **curs, t_glob_rules *rule,
		char (**matching)[255], char *end)
{
	if (**curs == '^' && (*curs)++)
		*matching = &rule->out;
	else
		*matching = &rule->in;
	if (**curs == ']' && *curs < end)
	{
		(*curs)++;
		(**matching)[']'] = 1;
	}
}

t_glob_rules	glob_rules_square(char **curs, t_list **rules, char add)
{
	char			*end;
	t_glob_rules	rule;
	char			(*matching)[255];

	ft_bzero(&rule, sizeof(t_glob_rules));
	rule.single = 1;
	end = square_find_end(*curs);
	check_first_char(curs, &rule, &matching, end);
	while (*curs < end)
	{
		if (!rules_square_range(curs, end, matching))
			rules_square_char(curs, end, matching);
		(*curs)++;
	}
	if (add)
		ft_lstaddback(rules, ft_lstnew(&rule, sizeof(t_glob_rules)));
	return (rule);
}
