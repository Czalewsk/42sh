/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 17:52:52 by maastie           #+#    #+#             */
/*   Updated: 2018/03/20 17:52:53 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char		**add_to_argv(char **argv, char *to_add)
{
	char	**k;
	int		i;
	int		a;

	i = 0;
	a = 0;
	k = ft_strsplit_whitespaces(to_add);
	while (k && k[i])
		i++;
	while (argv && argv[a])
		a++;
	i = a + i;
	free(to_add);
	return (concat_tab_for_sub(argv, k, i));
}

char		**concat_tab_for_sub(char **argv, char **k, int size)
{
	char	**ret;
	int		i;
	int		a;

	if (!argv)
		return (k);
	i = -1;
	a = 0;
	ret = (char **)ft_memalloc(sizeof(char *) * (size + 2));
	while (argv && argv[++i])
		ret[i] = ft_strdup(argv[i]);
	i > 1 ? i-- : i;
	while (k && k[a])
	{
		if (ret[i])
			ret[i] = ft_strjoin_free(ret[i], k[a++], 0);
		else
			ret[i] = ft_strdup(k[a++]);
		ret[++i] = NULL;
	}
	ft_free_array(argv);
	ft_free_array(k);
	return (ret);
}

char		*add_it_spaced(char *dst, char *src)
{
	char	*new;

	new = NULL;
	if (!dst)
		dst = ft_strdup(src);
	else
	{
		new = ft_strxjoin(4, dst, " ", src, "\0");
		free(dst);
		return (new);
	}
	return (dst);
}

char		**sub_shell_main(char **argv, char *cmd)
{
	DEBUG("\n\n\n\n\n%s\n\n\n\n\n", cmd);
	if ((argv = how_to_do(argv, cmd)) == NULL)
		sh_error(0, 0, NULL, 1, "parse error in command substitution");
	return (argv);
}

char		*extrac_from_backtite(char *dst, char *ref)
{
	int		i;
	int		e;

	i = 1;
	e = 0;
	while (ref && ref[i] && ref[i + 1])
	{
		dst[e] = ref[i++];
		e++;
	}
	dst[e++] = '\n';
	dst[e] = '\0';
	return (dst);
}
