/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:40:07 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/09 02:48:15 by czalewsk         ###   ########.fr       */
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
	ft_putstr_fd(C_DEFAULT, g_sh.fd_tty);
	ft_putstr_fd("[", g_sh.fd_tty);
	ft_putstr_fd(now + 11, g_sh.fd_tty);
	ft_putstr_fd("] ", g_sh.fd_tty);
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
	ft_putstr_fd(T_BOLD, g_sh.fd_tty);
	ft_putstr_fd(BLUE, g_sh.fd_tty);
	write(g_sh.fd_tty, hostname, ret);
	return (ret);
}

static int	sh_current_dir(int ret, char *path, char *home)
{
	char	*tmp;

	if (!(path = getcwd(path, 0)))
		return (0);
	ft_putstr_fd(CYAN, g_sh.fd_tty);
	ft_putstr_fd(T_BOLD, g_sh.fd_tty);
	if ((home = ft_getenv(g_sh.env, "HOME")) && !ft_strcmp(path, home))
	{
		ft_putstr_fd("~", g_sh.fd_tty);
		ret = 1;
	}
	else if (!(tmp = ft_strrchr(path, '/')))
		ret = 0;
	else if (!*(tmp + 1))
	{
		ft_putstr_fd("/ ", g_sh.fd_tty);
		ret = 2;
	}
	else
	{
		ft_putstr_fd(tmp + 1, g_sh.fd_tty);
		ret = ft_strlen(tmp + 1);
	}
	ft_strdel(&path);
	return (ret);
}

void		prompt_display(t_read *info, int new)
{
	int		ret;

	ret = 0;
	new ? write(g_sh.fd_tty, "\n", 1) : 0;
	ft_putstr_fd(!g_sh.exitstatus ? "🦆  " : "🐣  ", g_sh.fd_tty);
	ret += ft_strlen_utf8(!g_sh.exitstatus ? "🦆  " : "🐣  ");
	ret += sh_prompt_get_host();
	ret += sh_print_time();
	ret += sh_current_dir(0, NULL, NULL);
	ret += sh_prompt_git();
	ft_putstr_fd(" " YELLOW, g_sh.fd_tty);
	ft_putstr_fd(PROMPT, g_sh.fd_tty);
	ft_putstr_fd(C_DEFAULT, g_sh.fd_tty);
	ret += ft_strlen_utf8(PROMPT) + 1;
	info->prompt = ret;
}
