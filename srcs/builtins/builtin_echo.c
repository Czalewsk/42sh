/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:28:50 by bviala            #+#    #+#             */
/*   Updated: 2018/03/27 19:56:55 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void		echo_conv(char **str)
{
	int		num;
	int		len_num;
	char	tmp[4];

	DEBUG("str |%s|\n", *str);
	ft_memmove(*str - 1, *str + 1, ft_strlen(*str + 1) + 1);
	DEBUG("str 2|%s|\n", *str - 1);
		ft_strncpy(tmp, *str - 1, 3);
		num = ft_atoi(*str - 1);
		len_num = ft_count_len(num);
		if ((num > 0 && num <= 255) || (!num && *(*str - 1) == '0'))
		{
			DEBUG("tmp |%s|, num |%d| len |%d|\n", tmp, num, len_num);
			DEBUG("str now |%s|\n", *str - 1);
			*(*str - 1) = (char)num;
			DEBUG("str now |%s|\n", *str - 1);
			ft_memmove(*str, *str + len_num - 1, ft_strlen(*str + len_num - 1) + 1);
		}

		


//	echo_conv2(*str, 1, 1);
}

static size_t	ft_echo(const char *argv,
		char *str, int *const nonl, char *value)
{
	char const	key[] = { 'a', 'b', 'c', 'f', 'n', 'r', 't', 'v', '\\', 0 };
	char const	key_ascii[] = { 7, 8, 0, 12, 10, 13, 9, 11, 47, 0 };

	while (*str)
	{
		if (*str == '\\' && *(++str))
		{
			if ((value = ft_strchr(key, *str)))
			{
				str[-1] = key_ascii[value - key];
				ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
				if (*value == 'c')
				{
					*nonl = 1;
					return (str - argv - 1);
				}
			}
			else if (*str == '0')
			{
				DEBUG("before str - 1 |%s|, str |%s|\n", str - 1, str);
				echo_conv(&str);
				DEBUG("after str - 1 |%s|, str |%s|\n\n\n", str - 1, str);
			}
			else
				++str;
		}
		else if (*str)
			++str;
	}
	return (str - argv);
}

int				builtin_echo(t_process *p, int argc, char **argv, char **env)
{
	int		nonl;
	size_t	len;

	(void)argc;
	(void)env;
	if (write(p->stdout, "merci cedric, petit batard", 0) == -1)
		return (sh_error_bi(2, EXIT_FAILURE, 1,
					"echo : write error: Bad file descriptor\n"));
	argv++;
	if (!(nonl = 0) && *argv && !ft_strcmp(*argv, "-n"))
	{
		argv++;
		nonl = 2;
	}
	while (*argv && nonl != 1)
	{
		len = ft_echo(*argv, *argv, &nonl, NULL);
		ft_putnstr_fd(*argv, len, p->stdout);
		argv++;
		if (*argv)
			ft_putchar_fd(' ', p->stdout);
	}
	if (!nonl)
		ft_putchar_fd('\n', p->stdout);
	return (EXIT_SUCCESS);
}
