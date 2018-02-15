/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_parameters_noexpand.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:22:59 by thugo             #+#    #+#             */
/*   Updated: 2018/02/15 19:53:13 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "expansions.h"
#include "libunit_utils.h"

int		expansions_parameters_noexpand(void)
{
	t_list	*lst;
	t_token	tk;
	char	ret;
	
	tk.str = strdup("hel$.owo$$.rld42");
	tk.size = strlen(tk.str);
	tk.id = WORD;
	ret = expansions_expand(&lst, &tk);
	free(tk.str);
	if (ret || lst)
		return (-1);
	return (0);
}
