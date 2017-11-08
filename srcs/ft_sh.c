/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:10:34 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/08 13:38:54 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	read_key(t_key *entry)
{
	while ((entry->nread = read(0, entry->entry, SIZE_READ))  <= 0)
		if (entry->nread == -1)
			ft_error(strerror(errno), &restore_tty_param);
}
void	sh_prompt(t_read *info)
{
	static int first;

	if (first++)
		write(1, "\n\r", 2);
	ft_putstr(PROMPT);
	info->prompt = ft_strlen(PROMPT);
}

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_list history;
	char ret;
	termcaps_init(env);
	while(42)
	{
		init_info(&info);
		sh_prompt(&info);
		if ((ret = read_line() <= -1))
			break ;
		DEBUG(cmd->cmd);
		ft_strdel(&cmd.cmd);
	}
	termcaps_restore_tty();
	return (1);
}	

void	init_info(t_read *info)
{
	ft_bzero(info, sizeof(t_read));
	info->win_co = tgetnum("co");
}
