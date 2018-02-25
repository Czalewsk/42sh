/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 18:04:21 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/07 19:52:03 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

inline char		glob_check_char(unsigned char c)
{
	const char	test[255] = {['*'] = 1,
		['?'] = 2,
		['['] = 3 };

	return (test[c]);
}

/*
** Fonction de debug des rules charset
*/

void			print_charset(char charset[255])
{
	int		i;

	i = -1;
	while (++i < 255)
		ft_isprint(i) ? ft_printf("%3c ", i) : ft_printf("%3i ", i);
	write(g_sh.fd_tty, "\n", 1);
	i = -1;
	while (++i < 255)
		ft_printf("%3i ", charset[i]);
	write(g_sh.fd_tty, "\n", 1);
}

char			sh_glob(char *to_glob, t_list **files)
{
	t_list		*path;

	*files = NULL;
	if (!(path = sh_glob_init_path(to_glob)))
		return (0);
	glob_add_rules_to_path(path);
	return ((*files = glob_files_init(&path)) ? 1 : 0);
}
