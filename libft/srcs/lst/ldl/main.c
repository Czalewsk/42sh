/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:09:33 by bviala            #+#    #+#             */
/*   Updated: 2017/11/14 19:53:19 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

#define TEST_INIT
#define TEST_LIST_SORT
#define TEST_HEAD

static void	ldl_debug_display_list(t_ldl_head *ldl_list)
{
	t_ldl		*ldl;
	size_t			i;

	if (!ldl_list)
	{
		DEBUG("head = NULL\n");
		return ;
	}
	DEBUG("===> list length = |%d| <===\n", ldl_list->length);
	ldl = ldl_list->head;
	DEBUG("check ft_ldl_size= |%d|\n\n", ft_ldl_size(ldl_list));
	i = 1;
	while (ldl)
	{
		DEBUG("position : |%d|, data is |%s|\n", i, ldl->content);
//		if (i > 1)
//			DEBUG("              prev is |%s|, ", ldl->prev->content);
//		if (i < ldl_list->length)
//			DEBUG("next is |%s|\n\n", ldl->next->content);
		ldl = ldl->next;
		i++;
	}
	DEBUG("===> nodes crossed = |%d| <===\n\n", i - 1);
}

int			main(void)
{
	t_ldl_head	*ldl_list;

#ifdef TEST_INIT
//			DEBUG INIT
	if (!(ldl_list = ft_ldl_new_list()))
		return (0);
#endif
#ifdef TEST_LIST
//			DEBUG ADD && INSERT
	ft_ldl_addback(ldl_list, ft_strdup("barbu"));
	ft_ldl_addfront(ldl_list, ft_strdup("Bonjour"));
	ft_ldl_addback(ldl_list, ft_strdup("bennychou"));
	ft_ldl_addfront(ldl_list, ft_strdup("Bien le"));
	ft_ldl_insert(ldl_list, ft_strdup("Oh!"), 1);
	ft_ldl_insert(ldl_list, ft_strdup("mon beau"), 4);
	ft_ldl_insert(ldl_list, ft_strdup("avant mon beau"), 4);
	ft_ldl_insert(ldl_list, ft_strdup("chauve"), 7);
	ft_ldl_insert(ldl_list, ft_strdup("avant chauve"), 7);
	ft_ldl_insert(ldl_list, ft_strdup("fin"), 10);
	ldl_debug_display_list(ldl_list);
#endif
#ifdef TEST_LIST_SORT
	t_ldl *new, *new1, *new2, *new3;
	
	ft_ldl_new_node(&new, ft_strdup("ABC"));
	ft_ldl_new_node(&new1, ft_strdup("123"));
	ft_ldl_new_node(&new2, ft_strdup("xyz"));
	ft_ldl_new_node(&new3, ft_strdup("abc"));
	ft_ldl_insert_sort(ldl_list, new, &ft_strcmp);
	ft_ldl_insert_sort(ldl_list, new1, &ft_strcmp);
	ft_ldl_insert_sort(ldl_list, new2, &ft_strcmp);
	ft_ldl_insert_sort(ldl_list, new3, &ft_strcmp);
	ldl_debug_display_list(ldl_list);
#endif
#ifdef TEST_CLEAR
//			DEBUG CLEAR
	ft_ldl_clear(&ldl_list, &ft_strdel);
	ldl_debug_display_list(ldl_list);
#endif
#ifdef TEST_DEL
//			DEBUG DEL
	t_ldl *del;
	size_t	i;

	i = 1;
	del = ft_ldl_head(ldl_list);
	while (del && i < 1)
	{
		del = del->next;
		i++;
	}
	ft_ldl_del(ldl_list, &del, &ft_strdel);
	ldl_debug_display_list(ldl_list);
	i = 1;
	del = ft_ldl_head(ldl_list);
	while (del && i < 4)
	{
		del = del->next;
		i++;
	}
	ft_ldl_del(ldl_list, &del, &ft_strdel);
	ldl_debug_display_list(ldl_list);
	i = 1;
	del = ft_ldl_head(ldl_list);
	while (del && i < 8)
	{
		del = del->next;
		i++;
	}
	ft_ldl_del(ldl_list, &del, &ft_strdel);
	ldl_debug_display_list(ldl_list);
#endif
#ifdef TEST_DEL_IF
	ft_ldl_remove_if(ldl_list, &ft_strcmp, "bennychou", &ft_strdel);
	ldl_debug_display_list(ldl_list);
#endif
#ifdef TEST_REV
//			DEBUG REV
	ldl_list = ft_ldl_rev(ldl_list);
	ldl_debug_display_list(ldl_list);
#endif
#ifdef TEST_HEAD
//			DEBUG HEAD AND TAIL
	t_ldl *test;

	test = ft_ldl_head(ldl_list);
	DEBUG("debug head data is |%s|\n", test->content);
	test = ft_ldl_tail(ldl_list);
	DEBUG("debug tail data is |%s|\n", test->content);
	return (0);
#endif
}
