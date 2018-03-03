/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_getline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 14:36:32 by thugo             #+#    #+#             */
/*   Updated: 2017/04/11 14:39:57 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "minilib.h"
#include "libunit_types.h"

static t_ml_list	*get_elem(t_ml_list *lst, int fd)
{
	t_ml_list	*current;

	current = lst;
	while (current != NULL)
	{
		if (((t_u_gl *)current->content)->fd == fd)
			return (current);
		current = current->next;
	}
	return (NULL);
}

static void		del_elem(t_ml_list **lst, t_ml_list *elem)
{
	t_ml_list	*prev;
	t_ml_list	*cur;

	prev = NULL;
	cur = *lst;
	if (elem == *lst)
		*lst = elem->next;
	else
	{
		while (cur != NULL)
		{
			if (cur == elem && prev != NULL)
			{
				prev->next = elem->next;
				cur = NULL;
			}
			else
			{
				prev = cur;
				cur = cur->next;
			}
		}
	}
	free(elem->content);
	free(elem);
}

static int		read_buffer(char **line, char *buffer)
{
	int		i;
	char	*oldptr;

	i = -1;
	while (++i != -1)
	{
		if (buffer[i] == '\n' || buffer[i] == '\0')
		{
			oldptr = *line;
			*line = ml_strnjoin(*line, buffer, i);
			free(oldptr);
			if (*line == NULL)
				return (-1);
			if (buffer[i] == '\n')
			{
				memmove(buffer, &(buffer[i + 1]), GL_BUFF_SIZE - (size_t)i);
				return (1);
			}
			buffer[0] = '\0';
			i = -2;
		}
	}
	return (0);
}

static int		reader(const int fd, char **line, char *buffer)
{
	size_t		res;
	int			res_buffer;

	res = 1;
	if ((*line = ml_strnew(0)) == NULL)
		return (-1);
	while (res != 0)
	{
		if ((res_buffer = read_buffer(line, buffer)) == 1 || res_buffer == -1)
			return (res_buffer);
		res = read(fd, buffer, GL_BUFF_SIZE);
		if (res == (size_t)-1)
		{
			free(*line);
			*line = NULL;
			return (-1);
		}
		buffer[res] = '\0';
	}
	if (*line[0] != '\0')
		return (1);
	return (0);
}

int				utils_getline(const int fd, char **line)
{
	static t_ml_list	*lstfd;
	t_ml_list			*elem;
	t_u_gl				gl;
	int					res_reader;

	if (line == NULL)
		return (-1);
	if ((elem = get_elem(lstfd, fd)) == NULL)
	{
		gl.fd = fd;
		gl.buffer[0] = '\0';
		elem = ml_lstnew(&gl, sizeof(gl));
		if (elem == NULL)
			return (-1);
		ml_lstpush(&lstfd, elem);
	}
	if ((res_reader = reader(fd, line, ((t_u_gl *)elem->content)->buffer)) == 0)
	{
		free(*line);
		*line = NULL;
		del_elem(&lstfd, elem);
		return (0);
	}
	if (res_reader == -1)
		del_elem(&lstfd, elem);
	return (res_reader);
}
