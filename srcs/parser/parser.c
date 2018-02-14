/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:30:59 by maastie           #+#    #+#             */
/*   Updated: 2017/11/26 18:31:01 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern t_valid_res	g_valid_ress[];

int		place_token(t_token t)
{
	t_tree	*n;

	n = NULL;
	if (!head_tree)
	{
		if (t.id == NEWLINE)
			return (0);// je sais plus pk c est la -.-
		if (t.id != WORD && t.id != LPAR && t.id != If && t.id != While
			&& t.id != Until && t.id != Case && t.id != IO_NUMBER)
			return (-1);
		else if ((head_tree = init_node(t, head_tree)) == NULL)
			return (-3);
		current = head_tree;
		return (0);
	}
//	n = init_node(t, n);
	return (add_in_classic_tree(current, n = init_node(t, n)));
}

int		ft_leave_parse(t_token t)
{
	if (t.id == NEWLINE)
		ft_printf("\nError parsing near `\\n'\n", t.str); //
	else
		ft_printf("\nError parsing near `%s'\n", t.str); //
	if (t.str && t.str)
		free(t.str);
	return (-1);
}

int			read_parser(char **cmd, char *cur)
{
	int		ret;
	t_token	t;

	ret = 0;
	while ((ret = lexer_getnexttoken(&t, &cur, cmd)) != 0)
	{
		// if (t.id == IO_NUMBER)
		// 	ft_printf("\nIO_NUMBER BFORE = %s\n", t.str);
		if (t.id == NEWLINE)
		{
			 if (cnewline(t, cmd, cur) == -1)
				return (ft_leave_parse(t));
		}
		else if (place_token(t) < 0)
			return (ft_leave_parse(t));
	}
	return (ret);
}

int		parser(char **cmd)
{
	head_tree = NULL;
	char	*cur;

	cur = *cmd;
	if (read_parser(cmd, cur) == -1)
		return (ft_free_tree(head_tree));
	if (head_tree)
		return (ft_fill_for_jobs(head_tree));
	return (0);
}