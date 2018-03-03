/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_rules_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 08:39:01 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/03 16:44:07 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

static char		rules_check(unsigned char c, char (*charset_in)[255],
		char (*charset_out)[255])
{
	if ((*charset_out)[(unsigned int)c])
		return (-1);
	return ((*charset_in)[(unsigned int)c]);
}

char			rules_check_asterisk(char *str, t_list *rules,
		t_glob_rules *rule)
{
	char	ret;

	while (42)
	{
		ret = rules_check(*str, &rule->in, &rule->out);
		if ((ret == 1) &&
				(!rules->next ||
				glob_rules_check((*str ? str + 1 : str), rules->next)))
			return (1);
		if (ret < 0)
			return (0);
		if (!*str)
			return (rules ? 0 : 1);
		str++;
	}
	return (0);
}

char			glob_rules_check(char *str, t_list *rules)
{
	t_glob_rules	*rule;

	while (rules)
	{
		rule = rules->content;
		if (rule->single)
		{
			if (rules_check(*str, &rule->in, &rule->out) != 1)
				break ;
		}
		else
			return (rules_check_asterisk(str, rules, rule));
		if (!rule->dot && !*(str++))
			return (1);
		rules = rules->next;
	}
	return (rules ? 0 : 1);
}
