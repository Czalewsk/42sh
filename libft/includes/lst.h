/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:00:54 by bviala            #+#    #+#             */
/*   Updated: 2017/12/14 12:11:14 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H
# define FT_LDL_DEL_FIRST(list, del) ft_ldl_del_id(list, 1, del)
# define FT_LDL_DEL_LAST(list, del) ft_ldl_del_id(list, list->length, del)

# include "libft.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_ldl
{
	void			*content;
	struct s_ldl	*next;
	struct s_ldl	*prev;
}					t_ldl;

typedef struct		s_ldl_head
{
	size_t			length;
	struct s_ldl	*head;
	struct s_ldl	*tail;
}					t_ldl_head;

void				ft_lstrev(t_list **liste);
void				ft_lstprint(t_list **list);
void				ft_lstprint_name(t_list **list);
void				ft_lstclear(t_list **liste);
size_t				ft_lstsize(t_list *begin_list);
void				ft_lstaddback(t_list **alst, t_list *new);
void				ft_lstadd(t_list **alst, t_list *new, int index);
void				ft_lstiter(t_list *lst, void (*f) (t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f) (t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdel(t_list **alst, void (*del) (void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del) (void *, size_t));
t_list				*ft_lstswap(t_list *list);
void				ft_lstsort(t_list **begin_list, int (*cmp)());
t_list				*ft_lstnew_str(char *str, size_t content_size);
size_t				ft_lstlen(t_list *lst);

t_ldl_head			*ft_ldl_addback(t_ldl_head *ldl_head, void *content);
t_ldl_head			*ft_ldl_addfront(t_ldl_head *ldl_head, void *content);
void				ft_ldl_clear(t_ldl_head **ldl, void (*del)());
void				ft_ldl_del(t_ldl_head *ldl_head,
					t_ldl **ldl, void (*del)());
void				ft_ldl_del_id(t_ldl_head *ldl_head,
					size_t pos, void (*del)());
void				ft_ldl_del_if(t_ldl_head *ldl, int (*fcmp)(),
					void *content, void (*del)());
t_ldl_head			*ft_ldl_find(t_ldl_head *ldl_head, int (*fcmp)(),
					size_t size, void *content);
t_ldl				*ft_ldl_head(t_ldl_head *ldl);
t_ldl_head			*ft_ldl_insert(t_ldl_head *ldl, void *content, size_t pos);
t_ldl_head			*ft_ldl_insert_sort(t_ldl_head *ldl,
					t_ldl *new, int (*fcmp)());
t_ldl_head			*ft_ldl_new_list(void);
void				ft_ldl_new_node(t_ldl **ldl, void *content);
t_ldl_head			*ft_ldl_rev(t_ldl_head *ldl);
size_t				ft_ldl_size(t_ldl_head *ldl);
t_ldl				*ft_ldl_tail(t_ldl_head *ldl);
char				**ft_lfl_to_tab(t_ldl_head *ldl_head);
#endif
