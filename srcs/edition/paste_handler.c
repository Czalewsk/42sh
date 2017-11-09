/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:10:41 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/09 23:20:05 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			paste_detector(unsigned char test)
{
	static int			i;
	const unsigned char	paste_finish[6] = {27, 91, 50, 48, 49, 126};

	if (test == paste_finish[i])
	{
		i = (i == 5) ? 0 : i + 1;
		return ((i) ? 0 : -1);
	}
	else
	{
		i = 0;
		return (1);
	}
}

char		paste_handler(t_buf *cmd, t_read *info, t_key *entry)
{
	int		i;
	int		ret;


	// Traite (teste les char si ce sont des char de control...) 
	// avant de les copier dans cmd et actualiser info
	// Les char testés par paste_detector doivent etre sauvegardé dans un temp t_key
	// tant que paste_detector renvoit 0, s'il renvoit 1 les info peuvent etre 
	// traiter sinon cest la fin du coller
	(void)cmd;
	(void)info;
	i = 6;
	while ((ret = paste_detector(entry->entry[i])) >= 0)
	{
//		DEBUG("i=%d | ret=%d | char=%hhd\n", i, ret, entry->entry[i])
		if (i < entry->nread)
			i++;
		else
		{
			i = 0;
			read_key(entry);
		}
	}
	return (0);
}
