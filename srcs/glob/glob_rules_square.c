/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_rules_square.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 07:12:47 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/22 04:29:24 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

const char		g_special_char[] = "|&;<>()$`\\\"' \t\n";

char			*square_find_end(char *curs)
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
		curs++;
	}
	return (end);
}

static	char	rules_square_range(char **curs, char *end,
		char (*matching)[255], char assign)
{
	char	start_pttrn;
	char	*check;

	if (end - *curs < 2)
		return (0);
	check = *curs;
	if (*check == '\\')
		check++;
	if (check >= end)
		return (0);
	start_pttrn = *check;
	check++;
	if (check >= end || *check != '-')
		return (0);
	check++;
	if (*check == '\\')
		check++;
	if (check >= end || start_pttrn > *check)
		return (0);
	while (start_pttrn <= *check)
		(*matching)[(int)start_pttrn++] = assign;
	(*curs) = check;
	return (1);
}

static	void	rules_square_char(char **curs, char *end,
		char (*matching)[255], char assign)
{
	if (**curs == '\\' && (*curs) + 1 < end)
		(*curs)++;
	(*matching)[(int)**curs] = assign;
}

static	void	check_first_char(char **curs, char (*matching)[255],
		char *assign, char *end)
{
	++(*curs);
	if (**curs == '^' && (*curs)++)
	{
		ft_memset(matching, 1, 255);
		(*matching)['.'] = 0;
		*assign = 0;
	}
	else
		*assign = 1;
	if (**curs == ']' && *curs < end)
	{
		(*curs)++;
		(*matching)[']'] = *assign;
	}
}

t_glob_rules	glob_rules_square(char **curs, t_list **rules, char add)
{
	char			assign;
	char			*end;
	t_glob_rules	rule;

	ft_bzero(&rule, sizeof(t_glob_rules));
	rule.single = 1;
	end = square_find_end(*curs);
	check_first_char(curs, &rule.in, &assign, end);
	while (*curs < end)
	{
		if (!rules_square_range(curs, end, &rule.in, assign))
			rules_square_char(curs, end, &rule.in, assign);
		++(*curs);
	}
	if (!*rules && rule.in['.'] != assign)
		sh_glob_add_exp_dot(rules);
	if (add)
		ft_lstaddback(rules, ft_lstnew(&rule, sizeof(t_glob_rules)));
	++(*curs);
	return (rule);
}
