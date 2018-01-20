/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reserved.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 20:42:11 by maastie           #+#    #+#             */
/*   Updated: 2018/01/05 20:42:11 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern	t_for_close		g_for_closes[];

int				add_in_reserved_tree(t_tree *curr, t_tree *new)
{
	int		i;

	i = 0;
	set_new_id(curr, new);
	return (-1);
}

int				place_execpted_token(t_token t, t_tree *curent)
{
	t_tree	*n;

	n = NULL;
	return (add_in_reserved_tree(curent, init_node(t, n)));
}

t_token_id		closing(t_tree *ref)
{
	int			i;

	i = 0;
	while (g_for_closes[i].one)
	{
		if (g_for_closes[i].one == ref->token.id)
			return (g_for_closes[i].two);
		i++;
	}
	return (WORD);
}

int				read_for_reserved(t_tree *curr, char *cur, char *cmd)
{
	t_tree		*curent;
	t_token_id	last_execpted;
	t_token		t;
	int			ret;

	curent = curr;
	last_execpted = closing(curr);
	while ((ret = lexer_getnexttoken(&t, &cmd, &cur)) != 0)
	{
		if (ret < 0)
			return (-1);
		if (place_execpted_token(t, curent) < 0)
			return (-1);
		if (curent != curr && cur_is_new_res(curent) == 0)
		 	if (read_for_reserved(curent, cur, cmd) == -1)
		 		return (-1);
		 if (curent->token.id == last_execpted)
		 	return (0);
		 // trouver un moyen de check les intermediaire de while do done
		 // ex WHILE a; b && c; DO d; e || f; DONE Valid
		 // ex2 WHILE a; b && c; DO d; e || f; DO g; DONE Error
	}
	return (0);
}