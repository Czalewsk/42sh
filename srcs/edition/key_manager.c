/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 04:21:22 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/10 05:28:04 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_key_map		g_key_map[4] =
{
	{0, ARROW_L, 3, {27, 91, 68}, {&ft_strlen, NULL, NULL}},
	{1, ARROW_R, 3, {27, 91, 67}, {}},
	{2, ARROW_U, 3, {27, 91, 65}, {}},
	{3, ARROW_D, 3, {27, 91, 66}, {}}
};



static int	key_tokkeniser(t_key *entry)
{
	int		i;
	int		j;

	i = -1;
	while (++i < (int)sizeof(g_key_map))
	{
		j = 0;
		if (entry->nread == g_key_map[i].key_size)
		{
			while (j < entry->nread && entry->entry[j] == g_key_map[i].key[j])
				j++;
			if (j == entry->nread)
				return (i);
		}
	}
	return (-1);
}

void		key_manager(t_buf *cmd, t_read *info, t_key *entry)
{
	int		i;

	(void)cmd;
	(void)info;
	(void)entry;
	i = key_tokkeniser(entry);
	DEBUG("---i = %d function is %p\n", i, (i >= 0) ? g_key_map[i].function[0] : NULL)
}