/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 14:03:51 by thugo             #+#    #+#             */
/*   Updated: 2018/03/24 15:10:36 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static int	parse_arg(const char *arg, const char *options, char *asciitab,
		char *res)
{
	int	u;

	u = 0;
	while (arg[u])
	{
		if ((!options && ft_isalnum(arg[u])) || ft_strchr(options, arg[u]))
			asciitab[(int)arg[u]] = 1;
		else
		{
			res[0] = arg[u];
			res[1] = '\0';
			return (0);
		}
		++u;
	}
	return (1);
}

static void	save_res(const char *asciitab, char *res)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	while (i < 128)
	{
		if (asciitab[i])
			res[u++] = i;
		++i;
	}
	res[u] = '\0';
}

/*
** You must alloc res to options len + 1 or 128 + 1 if options is NULL.
**
** ft_getopt_buf add all unix options to the buf no malloc.
** Unix option start with '-', can contain multiple opt in the same argv.
** Unix option is only 1 char
** ft_getopt cannot parse long format option (--xxxxx)
** ft_getopt cannot parse option argument. (-l=xxx)
**
** const char *options: string allowed char(s), if NULL, all opts allowed.
** char *res: must be alloc in parent function.
** return:
**	the index of the next element of the argv array to be processed. (init 1)
**	-1 if has illegal option (not in options arg), the *res is illegal opt
*/

int			ft_getopt_buf(int argc, char **argv, const char *options, char *res)
{
	int		i;
	char	asciitab[128];

	*res = '\0';
	ft_bzero(asciitab, 128);
	i = 1;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "--"))
		{
			++i;
			break ;
		}
		else if (argv[i][0] == '-' && ft_strlen(argv[i]) > 1)
		{
			if (!parse_arg(argv[i] + 1, options, asciitab, res))
				return (-1);
		}
		else
			break ;
		++i;
	}
	save_res(asciitab, res);
	return (i);
}
