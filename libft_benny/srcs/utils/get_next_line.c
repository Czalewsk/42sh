/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 20:01:22 by bviala            #+#    #+#             */
/*   Updated: 2017/09/28 20:11:19 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	create_line(t_fd *current, char **line, char *tmp)
{
	char	*end;

	if ((end = ft_strchr(tmp, '\n')))
	{
		*end = '\0';
		if (current->save)
		{
			*line = ft_strjoin_free(current->save, tmp, 0);
			current->save = NULL;
		}
		else
			*line = ft_strdup(tmp);
		if (*end + 1)
			current->save = ft_strdup(end + 1);
		return (1);
	}
	return (0);
}

static int	get_full_line(t_fd *current, char **line, int i)
{
	char	tmp[BUFF_SIZE + 1];

	while ((i = read(current->fd, tmp, BUFF_SIZE)) > 0)
	{
		tmp[i] = '\0';
		if (create_line(current, line, tmp))
			break ;
		else
		{
			if (current->save == NULL)
				current->save = ft_strdup(tmp);
			else
				current->save = ft_strjoin_free(current->save, tmp, 0);
		}
	}
	if (i == 0 && current->save != NULL && ((ft_strchr(current->save, '\n'))
				== NULL) && current->save[0] != '\0')
	{
		*line = ft_strdup(current->save);
		ft_strdel(&current->save);
		return (1);
	}
	ft_strdel(&current->save);
	return (i > 0 ? 1 : i);
}

static int	check_save(t_fd *current, char **line)
{
	char	*end;

	if ((end = ft_strchr(current->save, '\n')))
	{
		*end = '\0';
		*line = ft_strdup(current->save);
		if (*end + 1)
			current->save = ft_strdup(end + 1);
		if (!current->save)
			return (0);
		return (1);
	}
	else
		return (get_full_line(current, line, 0));
}

static t_fd	*new_fd(const int fd)
{
	t_fd	*new;

	if (!(new = (t_fd*)malloc(sizeof(t_fd))))
		return (NULL);
	new->next = NULL;
	new->fd = fd;
	new->save = NULL;
	return (new);
}

int			get_next_line(const int fd, char **line)
{
	static t_fd	*begin_list = NULL;
	t_fd		*current;

	current = begin_list;
	if (fd < 0)
		return (-1);
	if (begin_list == NULL)
	{
		current = new_fd(fd);
		begin_list = current;
	}
	else
	{
		while (current->next && fd != current->fd)
			current = current->next;
		if (fd != current->fd)
		{
			current->next = new_fd(fd);
			current = current->next;
		}
	}
	if (current->save != NULL)
		return (check_save(current, line));
	return (get_full_line(current, line, 0));
}
