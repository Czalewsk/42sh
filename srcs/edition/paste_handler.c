/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:10:41 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/14 17:59:51 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	remove_excess(t_key *entry, int len)
{
	if (!len)
		return ;
	ft_memmove(entry->entry, entry->entry + len, entry->nread - len);
	entry->nread -= len;
}

static int	paste_end(char test)
{
	int			ret;
	static int	i;
	const char	paste_finish[6] = {'\e', '[', '2', '0', '1', '~'};
	const char	paste_finish2[7] = {'\e', '[', '2', -26, '0', '1', '~'};

	ret = 0;
	if (((i < 6) && test == paste_finish[i])
			|| ((i < 7) && test == paste_finish2[i]))
	{
		if ((i == 5 && test == paste_finish[i])
				|| (i == 6 && test == paste_finish2[i]))
			ret = -1;
		i = ret ? 0 : i + 1;
		return (ret);
	}
	else
	{
		i = 0;
		return (1);
	}
}

/*
**int			paste_start(char test)
**{
**	static int	i;
**	const char	paste_start[6] = {'\e', '[', '2', '0', '0', '~'};
**
**	if (test == paste_start[i])
**	{
**		i = (i == 5) ? 0 : i + 1;
**		return ((i) ? 0 : -1);
**	}
**	else
**	{
**		i = 0;
**		return (1);
**	}
**}
**
**char		is_pasted(t_key *entry)
**{
**	static int		i;
**	int		ret;
**	int
**
**	while (((ret = paste_start(entry->entry[i])) >= 0) || i < entry->nread)
**	{
**
**	}
**}
*/

char		paste_handler(t_buf *cmd, t_read *info, t_key *entry)
{
	int		i;
	int		ret;

	// Traite (teste les char si ce sont des char de control...)
	// avant de les copier dans cmd et actualiser info
	// Les char testés par paste_detector doivent etre sauvegardé dans un temp
	// t_key ant que paste_detector renvoit 0, s'il renvoit 1 les info peuvent
	// etre traiter sinon cest la fin du coller
	(void)cmd;
	(void)info;
	i = 6;
	while ((ret = paste_end(entry->entry[i])) >= 0)
	{
		DEBUG("i=%d | ret=%d | char=%hhd\n", i, ret, entry->entry[i]);
		if (i < entry->nread)
			i++;
		else
		{
			i = 0;
			read_key(entry);
		}
	}
	remove_excess(entry, i);
	return (0);
}
