/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_assign_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:24:51 by thugo             #+#    #+#             */
/*   Updated: 2018/03/07 14:25:13 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void			clear_assign_word(t_tree *cur, t_tree *new)
{
	while (cur)
	{
		if (cur->token.id == WORD)
		{
			new->token.id = WORD;
			return ;
		}
		cur = cur->previous;
	}
}
