/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compatibility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 16:08:24 by maastie           #+#    #+#             */
/*   Updated: 2017/12/14 16:08:25 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_tree							*cmpand_if(t_tree *current, t_token t)
{
	t_tree	*n;

	n = NULL;
	if (current->token.id != WORD && current->token.id != Fi && 
		current->token.id != Esac && current->token.id != Done &&
		current->token.id != SEMI)
		return (NULL);
	n = init_node(t, n);
	if (current->father == head_tree)
	{
		n->left = head_tree;
		head_tree = n;
		head_tree->father = n;
		current = n;
	}
	else
	{
		// cas du sciprt shell
		DEBUG("and_if Quel cas > ?\n");
	}
	return (current);
}

t_tree							*cmpand(t_tree *current, t_token t)
{
	t_tree	*n;

	n = NULL;
	if (current->token.id != WORD && current->token.id != Fi && 
		current->token.id != Esac && current->token.id != Done &&
		current->token.id != SEMI)
		return (NULL);
	n = init_node(t, n);
	if (current->father == head_tree)
	{
		n->left = head_tree;
		head_tree = n;
		head_tree->father = n;
		current = n;
	}
	else
	{
		//dans le shell script ?
		DEBUG("and Quel cas > ?\n");
	}
	return (current);
}

t_tree							*cmplpar(t_tree *current, t_token t)
{
	DEBUG("%s\n", t.str);
	return (current);
}

t_tree							*cmprpar(t_tree *current, t_token t)
{
	DEBUG("%s\n", t.str);
	return (current);
}

t_tree							*cmpdsemi(t_tree *current, t_token t)
{
	if (current->father->token.id != Case)
		return (NULL);
	(void)t;
	return (current);
}

t_tree							*cmpsemi(t_tree *current, t_token t)
{
	t_tree					*n;

	// just add to right !!!!! modifié les compatibilités de ce token
	if (current->token.id != WORD && current->token.id != Fi &&
		current->token.id != Esac && current->token.id != Done)
		return (NULL);
	n = NULL;
	n = init_node(t, n);
	current->right = n;
	n->father = current->father;
	current = n;

	//	t_tree	*n;
	// n = NULL;
	// if (current->token.id != WORD && current->token.id != Fi &&
	// 	current->token.id != Esac && current->token.id != Done)
	// 	return (NULL);
	// n = init_node(t, n);
	// if (current->father == head_tree)
	// {
	// 	n->left = head_tree;
	// 	head_tree = n;
	// 	head_tree->father = n;
	// 	current = n;
	// }
	// else
	// {
	// 	DEBUG("and Quel cas > ?\n");
	// }
	return (current);
}

t_tree							*cmpnewline(t_tree *current, t_token t)
{
	DEBUG("%s\n", t.str);
	return (current);
}

t_tree							*cmpor_if(t_tree *current, t_token t)
{
	t_tree	*n;

	n = NULL;
	if (current->token.id != WORD && current->token.id != Fi && 
		current->token.id != Esac && current->token.id != Done &&
		current->token.id != SEMI)
		return (NULL);
	n = init_node(t, n);
	if (current->father == head_tree)
	{
		n->left = head_tree;
		head_tree = n;
		head_tree->father = n;
		current = n;
	}
	else
	{
		DEBUG("or_if Quel cas > ?\n");
	}
	return (current);
}

t_tree							*cmppipe(t_tree *current, t_token t)
{
	t_tree					*n;

	n = NULL;
	if (current->token.id == AND_IF || current->token.id == OR_IF ||
		current->token.id == AND || current->token.id == DSEMI ||
		current->token.id == PIPE || current->token.id == Then ||
		current->token.id == Else || current->token.id == Elif ||
		current->token.id == Fi || current->token.id == Do ||
		current->token.id == Done || current->token.id == Esac)
		return (NULL);
	else
	{
		n = init_node(t, n);
		current->right = n;
		n->father = current->father;
		current = n;
		return (current);
	}
	return (NULL);
}

t_tree							*cmpdless(t_tree *current, t_token t)
{
	t_tree					*n;

	n = NULL;
	if (current->token.id == WORD || current->token.id == IO_NUMBER)
	{
		n = init_node(t, n);
		current->right = n;
		n->father = current->father;
		current = n;
		return (current);
		// valide
	}
	return (NULL);
}

t_tree							*cmpdgreat(t_tree *current, t_token t)
{
	t_tree					*n;

	n = NULL;
	if (current->token.id == WORD || current->token.id == IO_NUMBER)
	{
		n = init_node(t, n);
		current->right = n;
		n->father = current->father;
		current = n;
		return (current);
		// valide
	}
	return (NULL);
}

t_tree							*cmplessand(t_tree *current, t_token t)
{
	t_tree					*n;

	n = NULL;
	if (current->token.id == WORD || current->token.id == IO_NUMBER)
	{
		n = init_node(t, n);
		current->right = n;
		n->father = current->father;
		current = n;
		return (current);
		// valide
	}
	return (NULL);
}

t_tree							*cmpgreatand(t_tree *current, t_token t)
{
	t_tree					*n;

	n = NULL;
	if (current->token.id == WORD || current->token.id == IO_NUMBER)
	{
		n = init_node(t, n);
		current->right = n;
		n->father = current->father;
		current = n;
		return (current);
		// valide
	}
	return (NULL);
}

t_tree							*cmpdlessdash(t_tree *current, t_token t)
{
	DEBUG("%s\n", t.str);
	return (current);
}

t_tree							*cmplessgreat(t_tree *current, t_token t)
{
	DEBUG("%s\n", t.str);
	return (current);
}

t_tree							*cmpclobber(t_tree *current, t_token t)
{
	DEBUG("%s\n", t.str);
	return (current);
}

t_tree							*cmpless(t_tree *current, t_token t)
{
	t_tree					*n;

	n = NULL;
	if (current->token.id == WORD || current->token.id == IO_NUMBER)
	{
		n = init_node(t, n);
		current->right = n;
		n->father = current->father;
		current = n;
		return (current);
	}
	return (NULL);
}

t_tree							*cmpgreat(t_tree *current, t_token t)
{
	t_tree					*n;

	n = NULL;
	if (current->token.id == WORD || current->token.id == NEWLINE ||
		current->token.id == IO_NUMBER)
	{
		n = init_node(t, n);
		current->right = n;
		n->father = current->father;
		current = n;
		return (current);
	}
	return (NULL);
}

t_tree							*cmpif(t_tree *current, t_token t)
{
	DEBUG("%s\n", t.str);
	return (current);
}

t_tree							*cmpthen(t_tree *current, t_token t)
{
	DEBUG("%s\n", t.str);
	return (current);
}

t_tree							*cmpelse(t_tree *current, t_token t)
{
	DEBUG("%s\n", t.str);
	return (current);
}

t_tree							*cmpelif(t_tree *current, t_token t)
{
	DEBUG("%s\n", t.str);
	return (current);
}

t_tree							*cmpfi(t_tree *current, t_token t)
{
	DEBUG("%s\n", t.str);
	return (current);
}

t_tree							*cmpdo(t_tree *current, t_token t)
{
	DEBUG("%s\n", t.str);
	return (current);
}

t_tree							*cmpdone(t_tree *current, t_token t)
{
	DEBUG("%s\n", t.str);
	return (current);
}

t_tree							*cmpcase(t_tree *current, t_token t)
{
	DEBUG("%s\n", t.str);
	return (current);
}

t_tree							*cmpesac(t_tree *current, t_token t)
{
	DEBUG("%s\n", t.str);
	return (current);
}

t_tree							*cmpwhile(t_tree *current, t_token t)
{
	t_tree						*n;

	n = NULL;
	if (current->token.id == SEMI || current->token.id == AND ||
		current->token.id == OR_IF || current->token.id == AND_IF)
	{
		n = init_node(t, n);
		if (current->father == head_tree)
		{
			n->left = head_tree;
			head_tree->father = n;
			head_tree = n;
			current = n;			
		}
	}
	else
	{
		n = init_node(t, n);
		current->right = n;
		n->father = current->father;
		current = n;
		// simple word
	}
	return (current);
}

t_tree							*cmpuntil(t_tree *current, t_token t)
{
	DEBUG("%s\n", t.str);
	return (current);
}

t_tree							*cmpfor(t_tree *current, t_token t)
{
	DEBUG("%s\n", t.str);
	return (current);
}

t_tree							*cmpword(t_tree *current, t_token t)
{
	t_tree					*n;

	n = NULL;
	if (current->token.id == SEMI)
	{
		n = init_node(t, n);
		// if (current->father != current)
		// {
		// 	current->father->father = n;
		// 	n->left = current->father->father;
		// 	current = n;
		// }
		n->left = head_tree;
		head_tree = n;
		head_tree->father = n;
		current = n;
		// else
		// if 
		// {
		// 	n->left = head_tree;
		// 	current->father = n;
		// 	current = n;
		// // }
		// head_tree = n;
		return (current);
	}
	n = init_node(t, n);
	current->right = n;
	n->father = current->father;
	current = n;
	return (current);
}