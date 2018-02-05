/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:10:41 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/05 21:47:33 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

//Rajouter un etat dans la machine a etats de l'edition qui sactive lors de lajout
// d'un coller et qui va rewrite tout cmd->cmd afin d'enlever le surlignement
// du texte colle

static void	remove_excess(t_key *entry, int len)
{
	if (len <= 0 || entry->nread - len <= 0)
	{
		ft_bzero(entry, sizeof(t_key));
		return ;
	}
	ft_memmove(entry->entry, entry->entry + len, entry->nread - len);
	entry->nread -= len;
	ft_bzero(entry->entry + entry->nread, SIZE_BUFF - entry->nread - 1);
}

static int	paste_end(char test)
{
	static int	i;
	const char	paste_finish[6] = {'\e', '[', '2', '0', '1', '~'};

	if (test == paste_finish[i])
	{
		i = (i == 5) ? 0 : i + 1;
		return ((i ? 0 : -1));
	}
	else
	{
		i = 0;
		return (1);
	}
}

void		insert_chars_pasted_in(t_buf *cmd, t_read *info, t_buf *pasted)
{
	char	*curs;
	int		len;

	len = sh_curs_unicode(cmd->cmd, info->curs_char, 0);
	curs = cmd->cmd + len;
	ft_memmove(curs + pasted->size_actual, curs, sh_curs_unicode(cmd->cmd,
				ft_strlen(curs), 1));
	ft_memcpy(curs, pasted->cmd, pasted->size_actual);
	cursor_back_home(info);
	write(1, cmd->cmd, len);
	tputs(g_termcaps_cap[UNDER_START], 0, &ft_putchar_termcap);
	write(1, curs, pasted->size_actual);
	tputs(g_termcaps_cap[UNDER_STOP], 0, &ft_putchar_termcap);
	write(1, curs + pasted->size_actual, cmd->size_actual - len
			- pasted->size_actual);
}

void		insert_chars_pasted(t_buf *cmd, t_read *info, t_buf *pasted)
{
	int		len_visu;
	int		i;

	buff_handler(cmd, NULL, pasted->cmd);
	i = -1;
	while (*(pasted->cmd + (++i)))
		if (ft_isspace(*(pasted->cmd + i)))
			*(pasted->cmd + i) = ' ';
	cmd->size_actual += pasted->size_actual;
	if (info->curs_char == (long)info->total_char)
	{
		ft_strncat(cmd->cmd, pasted->cmd, pasted->size_actual);
		tputs(g_termcaps_cap[UNDER_START], 0, &ft_putchar_termcap);
		write(1, pasted->cmd, pasted->size_actual);
		tputs(g_termcaps_cap[UNDER_STOP], 0, &ft_putchar_termcap);
	}
	else
		insert_chars_pasted_in(cmd, info, pasted);
	len_visu = ft_strlen_utf8(pasted->cmd);
	info->curs_char += len_visu;
	info->total_char += len_visu;
	cursor_display_update(info, 1);
}

char		paste_handler(t_buf *cmd, t_read *info, t_key *entry)
{
	int		i;
	int		ret;
	t_buf	pasted;

	buff_handler(&pasted, NULL, NULL);
	i = 6;
	while ((ret = paste_end(entry->entry[i])) >= 0)
	{
		if (ret == 1)
			pasted.cmd[pasted.size_actual++] = *(entry->entry + i);
		if (i < entry->nread - 1)
			i++;
		else
		{
			i = 0;
			ft_bzero(entry, sizeof(t_key));
			buff_handler(&pasted, NULL, "             ");
			read_key(entry);
		}
	}
	insert_chars_pasted(cmd, info, &pasted);
	remove_excess(entry, i + 1);
	free(pasted.cmd);
	return (1);
}
