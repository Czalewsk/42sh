/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:23:18 by bviala            #+#    #+#             */
/*   Updated: 2017/12/08 18:17:42 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HISTORY_H
# define __HISTORY_H

# define HIST_FILE ".cedychou_history"

# include "ft_sh.h"

int		check_history_access(const char *file);
void	close_history(int clear, t_buf *cmd);
char	history_do(t_buf *cmd, t_read *info, t_key *entry);
char	history_mode(t_buf *cmd, t_read *info, t_key *entry);
char	history_up(t_buf *cmd, t_read *info, t_key *entry);
char	no_history_do(t_buf *cmd, t_read *info, int first);
char	no_history_up(t_buf *cmd, t_read *info, int last);
#endif
