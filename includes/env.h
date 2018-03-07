/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:41:02 by thugo             #+#    #+#             */
/*   Updated: 2018/03/05 19:12:41 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ENV_H
# define __ENV_H

# include "parser.h"

# define ENV_LOCAL	1
# define ENV_GLOBAL 2
# define ENV_TEMP	4
# define ENV_DELETE	8

typedef struct	s_env
{
	char	*var;
	char	type;
}				t_env;

void			env_init(const char **env);
char			*env_get(const char *name);
t_env			**env_getaddr(const char *name);
void			env_set(const char *name, const char *value, char type);
void			env_settype(const char *name, char type);
void			env_unset(const char *name);
void			env_unsetaddr(t_env **addr);
char			**env_make(char type);
size_t			env_len(const t_env **env, char type);
void			env_destroy(void);

t_tree			*assign_word(t_process *p, t_tree *c);

#endif
