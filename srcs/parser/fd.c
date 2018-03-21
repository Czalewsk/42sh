/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 19:44:57 by maastie           #+#    #+#             */
/*   Updated: 2018/03/19 11:48:37 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_tree	*ft_great(t_process *p, t_tree *c)
{
	if ((p->stdout = open(c->right->token.str, O_CREAT |
		O_TRUNC | O_WRONLY, 0755)) == -1)
	{
		sh_error(0, 0, NULL, 3, "Error: ",
			c->right->token.str, " open failed\n");
		return ((void *)1);
	}
	return (c->right->right);
}

t_tree	*land(t_process *p, t_tree *c)
{
	if (ft_isint(c->right->token.str) == 1)
	{
		p->stdin = ft_atoi(c->right->token.str);
		if (fcntl(p->stdin, F_GETFD) == -1)
		{
			sh_error(0, 0, NULL, 3, "Error: ",
				c->right->token.str, " is not set as file descriptor\n");
			return ((void *)1);
		}
		p->stderr = p->stdout;
		return (c->right->right);
	}
	if (!ft_memcmp(c->right->token.str, "-", ft_strlen(c->right->token.str)))
	{
		p->stdin = -1;
		return (c->right->right);
	}
	p->stderr = p->stdout;
	sh_error(-1, 0, NULL, 1, "Error: file number execpted\n");
	return ((void *)1);
}

t_tree	*gand(t_process *p, t_tree *c)
{
	if (ft_isint(c->right->token.str) == 1)
	{
		p->stdout = ft_atoi(c->right->token.str);
		if (fcntl(p->stdout, F_GETFD) == -1)
		{
			sh_error(0, 0, NULL, 3, "Error: ",
				c->right->token.str, " is not set as file descriptor\n");
			return ((void *)1);
		}
	}
	else if (!ft_memcmp("-", c->right->token.str, 1))
	{
		p->closeout = 1;
		return (c->right->right);
	}
	else if ((p->stdout = open(c->right->token.str, O_CREAT |
					O_TRUNC | O_WRONLY, 0755)) == -1)
	{
		sh_error(0, 0, NULL, 3, "Error: ",
				c->right->token.str, " open failed\n");
		return ((void *)1);
	}
	p->stderr = p->stdout;
	return (c->right->right);
}

t_tree	*ft_dgreat(t_process *p, t_tree *c)
{
	if ((p->stdout = (open(c->right->token.str, O_APPEND |
		O_CREAT | O_WRONLY, 0755))) == -1)
	{
		sh_error(0, 0, NULL, 3, "Error: ",
			c->right->token.str, " open failed\n");
		return ((void *)1);
	}
	return (c->right->right);
}

t_tree	*ft_less(t_process *p, t_tree *c)
{
	if ((p->stdin = (open(c->right->token.str, O_RDONLY, 0755))) == -1)
	{
		sh_error(0, 0, NULL, 3, "Error: ",
			c->right->token.str, " open failed\n");
		return ((void *)1);
	}
	return (c->right->right);
}
