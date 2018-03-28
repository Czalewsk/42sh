/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:30:59 by maastie           #+#    #+#             */
/*   Updated: 2018/03/23 11:40:52 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern t_valid_res	g_valid_ress[];
t_tree	*g_head_tree;
t_tree	*g_current;
t_list	*g_here_list;

int			place_token(t_token t)
{
	t_tree	*n;

	n = NULL;
	if (!g_head_tree)
	{
		if (t.id == NEWLINE)
			return (0);
		if (t.id != WORD && t.id != IO_NUMBER && t.id != SUBSH
			&& t.id != LESSAND && t.id != ASSIGNMENT_WORD
			&& t.id != GREATAND && t.id != ANDGREAT
			&& t.id != LESS && t.id != GREAT && t.id != DGREAT && t.id != DLESS)
			return (-1);
		else if ((g_head_tree = init_node(t, g_head_tree)) == NULL)
			return (-3);
		g_current = g_head_tree;
		return (0);
	}
	return (add_in_classic_tree(g_current, n = init_node(t, n)));
}

int			ft_leave_parse(t_token t, int k)
{
	if (k == 1)
	{
		if (t.str)
			free(t.str);
		return (-1);
	}
	if (t.id == NEWLINE)
		sh_error(0, 1, NULL, 1, "Error parsing near `\\n'");
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
		sh_escape(n->str);
		ft_memcpy(&t, n, sizeof(t_token));
		free(n);
		if (place_token(t) < 0)
			return (ft_leave_parse(t, 0));
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
		if (!(ret = expansions_expand(&lst, &t)))
		{
			sh_escape(t.str);
			if (t.id == NEWLINE)
			{
				if (cnewline(t, cmd, &cur) == -1)
					return (ft_leave_parse(t, 0));
			}
			else if ((ret = place_token(t)) < 0)
				return (ret_douille(ret, t));
		}
		else if (ret == -1)
			return (ft_leave_parse(t, 1));
		else if (take_token_from_list(lst, t) == -1)
			return (-1);
	}
	return (ret);
}

int			parser(char **cmd)
{
	char	*cur;
	int		i;

	cur = *cmd;
	g_head_tree = NULL;
	g_current = NULL;
	i = read_parser(cmd, cur);
	if (i == -1 || i == -2)
	{
		ft_free_tree(g_head_tree);
		return (-1);
	}
	if (g_head_tree)
		return (ft_fill_for_jobs(g_head_tree));
	return (0);
}
