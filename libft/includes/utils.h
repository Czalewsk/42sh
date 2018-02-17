/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:58:44 by bviala            #+#    #+#             */
/*   Updated: 2018/02/14 14:47:40 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>

# define BUFF_SIZE 10000
# define CT(Pointeur) ((t_str*)(Pointeur->content))

typedef struct		s_str
{
	int				fd;
	char			*buff;
	int				size;
}					t_str;

int					ft_count_len(int nb);
int					ft_howmany(char *line, char c);
int					ft_islower(int c);
int					ft_isalpha(int n);
int					ft_isdigit(int n);
int					ft_isalnum(int n);
int					ft_isascii(int n);
int					ft_isprint(int n);
int					ft_isspace(int c);
int					ft_is_a_bin(const char *path);
int					ft_is_a_dir(const char *path);
int					ft_is_a_file(const char *path);
int					ft_is_a_reg_file(const char *path);
int					ft_toupper(int n);
int					ft_tolower(int n);
int					ft_isupper(int nb);
void				ft_swap(void **a, void **b);
void				ft_sort_wordtab(char **tab);
void				ft_rev_wordtab(char **tab);
int					get_next_line(const int fd, char **line);
void				ft_error(char *str, void (*f)(void));
int					ft_iswcntrl(unsigned int c);
t_list				*ft_list_files(char *path);
int					ft_is_not_root(char *name);
int					ft_strisnumber(char *str);
int					ft_find_end_nbr(char *str);
int					ft_isint(char *nb);
char				ft_is_escape(char *esc, char *str);
t_list				*ft_list_folders(char *path);

#endif
