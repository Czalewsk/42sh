/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 07:51:35 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/01 07:52:48 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

static char	glob_check_pattern(char *str)
{
	char	*curs;

	if (!(curs = str))
		return (0);
	while (*curs && (!glob_check_char(*curs) || ft_is_escape(curs, str)))
		++curs;
	return (*curs ? 1 : 0);
}

t_list		*sh_glob_init_path(char *to_glob)
{
	char	*last_slash;
	t_list	*path;

	if (!glob_check_pattern(to_glob))
		return (NULL);
	path = NULL;
	last_slash = to_glob;
	to_glob -= 1;
	while (++to_glob)
		if (*to_glob == '/' || !*to_glob)
		{
			ft_lstaddback(&path,
				ft_lstnew_str(ft_strsub(last_slash, 0,
					(to_glob - last_slash) + 1), 0));
			if (!*(last_slash = to_glob + 1) || !*to_glob)
				break ;
		}
	return (path);
}
