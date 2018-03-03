/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:05:00 by bviala            #+#    #+#             */
/*   Updated: 2018/02/27 11:47:30 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __DEBUG_H
# define __DEBUG_H

# include "libft.h"
# include <fcntl.h>

# define DEBUG_WINDOW ("/dev/ttys002")
# define DEBUG(x...) (debug(x));

int		debug(char *format, ...);

#endif
