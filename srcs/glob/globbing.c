/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 16:58:43 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/11 17:08:45 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

static void	get_address_end(t_list ***tmp)
{
	if (!**tmp)
		return ;
	while (**tmp)
		*tmp = &(**tmp)->next;
	return ;
}

char		get_globbing(char *tkkn, t_list **res)
{
	t_list	*tmp;
	t_list	*final;
	t_list	*glob;
	t_list	**to_add;

	if (!*res)
		return (sh_glob(tkkn, res));
	final = NULL;
	to_add = &final;
	tmp = *res;
	while (tmp)
	{
		get_address_end(&to_add);
		if (sh_glob(tmp->content, &glob))
			*to_add = glob;
		else
			*to_add = ft_lstnew(tmp->content, ft_strlen(tmp->content) + 1);
		tmp = tmp->next;
	}
	ft_lstdel(res, &ft_lst_del_str);
	*res = final;
	return (1);
}

char		sh_globbing(char *tkkn, t_list **result)
{
	char	matching;

	*result = NULL;
	matching = 0;
	if (sh_brace_exp(tkkn, result))
		matching = 1;
	if (get_globbing(tkkn, result))
		matching = 1;
	return (matching);
}
