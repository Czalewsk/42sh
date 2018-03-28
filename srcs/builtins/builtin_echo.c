/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:28:50 by bviala            #+#    #+#             */
/*   Updated: 2018/03/28 16:27:06 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int		count_len_oct(char tmp[4])
{
	int		len;

	len = 0;
	while (tmp[len] >= '0' && tmp[len] < '8')
		len++;
	return (len);
}

static void		echo_conv(char **str)
{
	int		num;
	int		len_num;
	char	tmp[4];

	ft_memmove(*str - 1, *str, ft_strlen(*str) + 1);
	if (!**str || **str < '0' || **str > '7')
	{
		*(*str - 1) = 0;
		return ;
	}
	ft_strncpy(tmp, *str, 3);
	len_num = count_len_oct(tmp);
	tmp[len_num] = 0;
	num = ft_atoi_base(tmp, "01234567");
	*(*str - 1) = num;
	ft_memmove(*str, *str + len_num, ft_strlen(*str + len_num) + 1);
}

static int		ft_echo(const char *av, char *s, int *const nonl, char *value)
{
	char const	key[] = { 'a', 'b', 'c', 'f', 'n', 'r', 't', 'v', '\\', 0 };
	char const	key_ascii[] = { 7, 8, 0, 12, 10, 13, 9, 11, 47, 0 };

	while (*s)
	{
		if (*s == '\\' && *(++s))
		{
			if ((value = ft_strchr(key, *s)))
			{
				s[-1] = key_ascii[value - key];
				ft_memmove(s, s + 1, ft_strlen(s + 1) + 1);
				if (*value == 'c' && (*nonl = 1))
					return (s - av - 1);
			}
			else if (*s == '0')
				echo_conv(&s);
			else
				++s;
		}
		else if (*s)
			++s;
	}
	return (s - av);
}

static int		ft_onlyn(char *str)
{
	if (*str != '-')
		return (0);
	while (*(++str))
	{
		if (*str && *str != 'n')
			return (0);
	}
	return (1);
}

int				builtin_echo(t_process *p, int argc, char **argv, char **env)
{
	int		nonl;

	(void)argc;
	(void)env;
	if (write(p->stdout, "merci cedric, petit batard", 0) == -1)
	{
		return (sh_error_bi(2, EXIT_FAILURE, 1,
					"echo : write error: Bad file descriptor\n"));
	}
	argv++;
	if (!(nonl = 0) && *argv && (!ft_strcmp(*argv, "-n") || ft_onlyn(*argv)))
	{
		argv++;
		nonl = 2;
	}
	while (*argv && nonl != 1)
	{
		write(p->stdout, *argv, ft_echo(*argv, *argv, &nonl, NULL));
		argv++;
		if (*argv)
			ft_putchar_fd(' ', p->stdout);
	}
	if (!nonl)
		ft_putchar_fd('\n', p->stdout);
	return (EXIT_SUCCESS);
}
