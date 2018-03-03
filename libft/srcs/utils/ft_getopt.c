/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 00:18:22 by thugo             #+#    #+#             */
/*   Updated: 2018/02/27 15:27:14 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static int	parse_arg(const char *arg, const char *options, char *asciitab,
		char **res)
{
	int	u;

	u = 0;
	while (arg[u])
	{
		if ((!options && ft_isalnum(arg[u])) || ft_strchr(options, arg[u]))
			asciitab[(int)arg[u]] = 1;
		else
		{
			if (!(*res = ft_strndup(arg + u, 1)))
				exit(EXIT_FAILURE);
			return (0);
		}
		++u;
	}
	return (1);
}

static void	save_res(const char *asciitab, char **res)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	while (i < 128)
	{
		if (asciitab[i++])
			++u;
	}
	if (!(*res = ft_strnew(u)))
		exit(EXIT_FAILURE);
	i = 0;
	u = 0;
	while (i < 128)
	{
		if (asciitab[i])
			(*res)[u++] = i;
		++i;
	}
}

/*
** ft_getopt add all unix options to the buf.
** Unix option start with '-', can contain multiple opt in the same argv.
** Unix option is only 1 char
** ft_getopt cannot parse long format option (--xxxxx)
** ft_getopt cannot parse option argument. (-l=xxx)
**
** const char *options: string allowed char(s), if NULL, all opts allowed.
** char *res: malloc string with option(s) parse.
** return:
**	the index of the next element of the argv array to be processed. (init 1)
**	-1 if has illegal option (not in options arg), the *res is illegal opt
*/

int			ft_getopt(int argc, char **argv, const char *options, char **res)
{
	int		i;
	char	asciitab[128];

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
