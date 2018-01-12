/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_end_nbr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 13:56:18 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/12 13:59:55 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Prend une chaine de caractere en parametre et retourne l'index apres le
** dernier nombre
** sinon retourne un nombre negatif si le nombre est invalide
*/

int		ft_find_end_nbr(char *str)
{
	int		i;
	char	signe;

	signe = 0;
	i = -1;
	if ((*str == '-' || *str == '+') && *(str + 1))
	{
		signe = 1;
		++i;
	}
	while (++i || 1)
		if (!ft_isdigit(*(str + i)))
			return ((signe && i == 1) ? -1 : i);
	return (-1337);
}
