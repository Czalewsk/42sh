/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:30:59 by maastie           #+#    #+#             */
/*   Updated: 2018/03/05 15:33:22 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern t_valid_res	g_valid_ress[];

int			place_token(t_token t)
{
	t_tree	*n;

	n = NULL;
	if (!head_tree)
	{
		if (t.id == NEWLINE)
			return (0);
		if (t.id != WORD && t.id != LPAR && t.id != IO_NUMBER && t.id != SUBSH
				&& t.id != ASSIGNMENT_WORD)
			return (-1);
		else if ((head_tree = init_node(t, head_tree)) == NULL)
			return (-3);
		current = head_tree;
		return (0);
	}
	return (add_in_classic_tree(current, n = init_node(t, n)));
}

int			ft_leave_parse(t_token t)
{
	if (t.id == NEWLINE)
		sh_error(0, 0, NULL, 1, "Error parsing near `\\n'\n");
	else
	{
		sh_error(0, 0, NULL, 3, "Error parsing near `", t.str, "`\n");
		if (t.str)
			free(t.str);
	}
	return (-1);
}

int			take_token_from_list(t_list *lst, t_token c)
{
	t_list	*tmp;
	t_list	*f;
	t_token	*n;
	t_token	t;

	tmp = lst;
	free(c.str);
	while (tmp)
	{
		f = tmp;
		n = (t_token *)tmp->content;
		ft_memcpy(&t, n, sizeof(t_token));
		free(n);
		if (place_token(t) < 0)
			return (ft_leave_parse(t));
		tmp = tmp->next;
		free(f);
	}
	return (0);
}

int			read_parser(char **cmd, char *cur)
{
	int		ret;
	t_list	*lst;
	t_token	t;

	ret = 0;
	while ((ret = lexer_getnexttoken(&t, &cur, cmd)) > 0)
	{
		if (!expansions_expand(&lst, &t))
		{
			if (t.id == NEWLINE)
			{
				if (cnewline(t, cmd, cur) == -1)
					return (ft_leave_parse(t));
			}
			else if (place_token(t) < 0)
				return (ft_leave_parse(t));
		}
		else
			return (take_token_from_list(lst, t));
	}
	return (ret);
}

int			parser(char **cmd)
{
	char	*cur;
	int		i;

	cur = *cmd;
	head_tree = NULL;
	i = read_parser(cmd, cur);
	if (i == -1 || i == -2)
	{
		ft_free_tree(head_tree);
		return (-1);
	}
	if (head_tree)
		return (ft_fill_for_jobs(head_tree));
	return (0);
}