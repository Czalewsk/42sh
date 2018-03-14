/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_and_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 12:54:31 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/11 12:57:55 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		dup_and_close(int new, int old, int closed)
{
	dup2(new, old);
	close(closed);
}
