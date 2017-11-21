/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:23:18 by bviala            #+#    #+#             */
/*   Updated: 2017/11/21 17:32:32 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HISTORY_H
# define __HISTORY_H

# define HIST_FILE "/Users/bviala/.bash_history"

# include "ft_sh.h"

char	history_mode(t_buf *cmd, t_read *info, t_key *entry);
#endif
