/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:58:44 by bviala            #+#    #+#             */
/*   Updated: 2017/09/14 17:06:36 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

# define BUFF_SIZE 250

typedef struct		s_fd
{
	int				fd;
	char			*save;
	struct s_fd		*next;
}					t_fd;

int					ft_islower(int c);
int					ft_isalpha(int n);
int					ft_isdigit(int n);
int					ft_isalnum(int n);
int					ft_isascii(int n);
int					ft_isprint(int n);
int					ft_isspace(int c);
int					ft_toupper(int n);
int					ft_tolower(int n);
int					ft_isupper(int nb);
void				ft_swap(void **a, void **b);
void				ft_sort_wordtab(char **tab);
void				ft_rev_wordtab(char **tab);
int					get_next_line(const int fd, char **line);

#endif
