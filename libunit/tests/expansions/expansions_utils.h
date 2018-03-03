/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:44:43 by thugo             #+#    #+#             */
/*   Updated: 2018/02/19 03:31:12 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_UTILS
# define EXPANSIONS_UTILS

# include "ft_sh.h"
# include "expansions.h"

extern t_sh	g_sh;

int		expansions_utils_free(char ***venv, t_list **lst, int ret);

#endif
