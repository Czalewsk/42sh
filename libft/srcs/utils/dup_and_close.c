/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_and_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 12:54:31 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/16 12:09:25 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		dup_and_close(int new, int old, int closed)
{
	dup2(new, old);
	close(closed);
}
