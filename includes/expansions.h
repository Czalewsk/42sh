/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 19:23:47 by thugo             #+#    #+#             */
/*   Updated: 2018/01/27 16:19:26 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "lexer_types.h"
# include "libft.h"

t_list		*expansions_expand(t_token *tk);
t_list		*expand_parameters(t_token *tk);

#endif
