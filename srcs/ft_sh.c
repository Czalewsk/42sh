/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:10:34 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/04 15:40:07 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			g_edition_state = 0;

inline void	info_init(t_read *info)
{
	struct winsize	ws;

	ft_bzero(info, sizeof(t_read));
	ioctl(1, TIOCGWINSZ, &ws) ? ft_bzero(&ws, sizeof(ws)) : 0;
	info->win_co = ws.ws_col;
}

int			main(int ac, char **av, char **env)
{
	t_buf		cmd;
	t_read		info;
	char		ret;

	ret = 0;
	termcaps_init(env);
	while (ac || av)
	{
		info_init(&info);
		prompt_display(&info);
		if ((ret = read_line(&cmd, &info)) == -1)
			break ;
		if (ret == -3)
			continue ;
		DEBUG("\r\nCMD=|%s|", cmd.cmd);
	/* TEST GLOB FIND PATTERN	*/
	t_list *resultat = sh_brace_exp(cmd.cmd);
	t_list *tmp;
	tmp = resultat;
	write(1,"\n",1);
	while (tmp)
	{
		ft_printf(" %s", tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&resultat);
	write(1,"\n",1);
	/* FIN DU TEST*/
		ft_strdel(&cmd.cmd);
	}
	ft_strdel(&cmd.cmd);
	termcaps_restore_tty();
	return (ret);
}
