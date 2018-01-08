/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 07:51:35 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/08 10:29:19 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

t_list		*sh_glob_init_path(char *to_glob)
{
	char	*curs;
	char	*last_slash;
	t_list	*path;
	int		len;

	last_slash = to_glob;
	curs = to_glob;
	while (*curs && !glob_check_char(*curs))
		++curs;
	if (!(path = NULL) && !curs)
		return (NULL);
	curs = to_glob - 1;
	while (++curs)
		if (*curs == '/' || !*curs)
		{
			len = (curs - last_slash) + 1;
			ft_lstaddback(&path,
					ft_lstnew_str(ft_strsub(last_slash, 0, len), 0));
			last_slash = curs + 1;
			if (!*(last_slash) || !*curs)
				break ;
		}
	return (path);
}
