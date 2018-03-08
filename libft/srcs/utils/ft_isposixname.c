/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isposixname.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 17:39:21 by thugo             #+#    #+#             */
/*   Updated: 2018/03/08 17:50:51 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isposixname(char *name)
{
	if (ft_isdigit(*name) || (*name != '_' && !ft_isalpha(*name)))
		return (0);
	while (*(++name))
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
	return (1);
}
