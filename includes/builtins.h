/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 19:13:08 by bviala            #+#    #+#             */
/*   Updated: 2018/03/08 19:52:49 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BUILTINS_H
# define __BUILTINS_H

# include "ft_sh.h"

char	builtin_history(void);
int		builtin_export(t_process *p, int argc, char **argv, char **env);

#endif
