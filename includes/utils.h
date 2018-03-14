/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 21:58:39 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/15 00:13:18 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILS_H
# define __UTILS_H

# include "ft_sh.h"

/*
** DEFINE ESCAPE
*/
# define SH_IS_ESC(str, i) (*(str + i) & 1)
# define SH_IS_END_DQ(str, i) (*(str + i) & 2)

/*
**	DEFINE STATS
*/
# define STATS_EXIST	1
# define STATS_EXEC		2
# define STATS_DIR		4

void		sh_escape(char *str);
char		sh_globbing(char *tkkn, t_list **result);
char		*escape_it(char *str);
char		sh_error(char ret, char new_line, void (*f_callback)(),
			int nb, ...);
char		sh_error_bi(int fd, char ret, int nb, ...);
void		sh_savefds(int savefds[3]);
void		sh_restorefds(int savefds[3]);
void		update_display_init(t_read *info, t_buf *cmd);
void		update_display(void);
char		stats_check(const char *path);
int			stats_filecmp(const char *p1, const char *p2);
void		cwd_init(void);
void		cwd_change(const char *path);
void		cwd_destroy(void);

#endif
