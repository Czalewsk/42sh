/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:40:07 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/11 02:40:35 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	sh_print_time(void)
{
	time_t	t;
	char	*now;

	time(&t);
	now = ctime(&t);
	*(now + 16) = '\0';
	ft_putstr(C_DEFAULT);
	ft_putstr("[");
	ft_putstr(now + 11);
	ft_putstr("] ");
	return (8);
}

static int	sh_prompt_get_host(void)
{
	int		ret;
	char	hostname[1024];

	if (gethostname(hostname, 1024))
		return (0);
	hostname[1023] = '\0';
	if (ft_strlen(hostname) > 15)
		return (0);
	ret = ft_strchr(hostname, '.') - hostname;
	ret = ret > 0 ? ret + 1 : ft_strlen(hostname) + 1;
	hostname[ret - 1] = ' ';
	ft_putstr(T_BOLD);
	ft_putstr(BLUE);
	write(1, hostname, ret);
	return (ret);
}

static int	sh_current_dir(int ret, char *path, char *home)
{
	char	*tmp;

	if (!(path = getcwd(path, 0)))
		return (0);
	ft_putstr(CYAN);
	ft_putstr(T_BOLD);
	if ((home = ft_getenv(g_sh.env, "HOME")) && !ft_strcmp(path, home))
	{
		ft_putstr("~");
		ret = 1;
	}
	else if (!(tmp = ft_strrchr(path, '/')))
		ret = 0;
	else if (!*(tmp + 1))
	{
		ft_putstr("/ ");
		ret = 2;
	}
	else
	{
		ft_putstr(tmp + 1);
		ret = ft_strlen(tmp + 1);
		ft_strdel(&path);
	}
	return (ret);
}

void		prompt_display(t_read *info, int new)
{
	int		ret;

	ret = 0;
	new ? write(1, "\n", 1) : 0;
	g_sh.exitstatus = 2;
	ft_putstr(!g_sh.exitstatus ? "🦆  " : "🐣  ");
	ret += ft_strlen_utf8(!g_sh.exitstatus ? "🦆  " : "🐣  ");
	ret += sh_prompt_get_host();
	ret += sh_print_time();
	ret += sh_current_dir(0, NULL, NULL);
	ret += sh_prompt_git();
	ft_putstr(" " YELLOW);
	ft_putstr(PROMPT);
	ft_putstr(C_DEFAULT);
	ret += ft_strlen_utf8(PROMPT) + 1;
	info->prompt = ret;
}
