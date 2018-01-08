/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 18:04:21 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/08 08:30:45 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

inline char		glob_check_char(int c)
{
	const char	test[255] = {['*'] = 1,
		['?'] = 2,
		['['] = 3 };

	return (test[(unsigned)c]);
}

/*
void			glob_star(char *to_glob, t_list *rules)
{

}

t_list			*sh_glob_init(char *to_glob)
{
	char	*last_slash;
	char	*curs;
	char	c;
	t_list	*rules;
	void	(*const f[4])(char *, t_list *) = {NULL, &glob_star, NULL, NULL};

	rules = NULL;
	curs = to_glob;
	while (curs)
	{
		if (*curs == '/')
			last_slash = 
		if ((c = glob_check_char(*curs)) && ft_is_escape(curs, to_glob))
			f[(int)c](to_glob, rules);
	}
	return (rules);
}
*/

t_list			*sh_glob(char *to_glob)
{
	t_list		*path;

	/* Remove '\n' at the end of the line */
	char *nl = ft_strrchr(to_glob, '\n');
	if (nl)
		*nl = '\0';
	/* END */
	path = sh_glob_init_path(to_glob);
	/* DEBUG */
	t_list *tmp_path = path;
	write(1, "\n", 1);
	while (tmp_path)
	{
		ft_printf("|%s|\n", tmp_path->content);
		tmp_path = tmp_path->next;
	}
	/* END */
	return (NULL);
}
