/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_write_wchar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 17:45:05 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/19 18:16:44 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"


static	void	wchar_to_char(int wchar, char **str)
{
	int					n;
	unsigned	int		msk;
	int					i;

	msk = 1;
	n = 2;
	while ((wchar >> (7 + (n * 4 + n / 2))) == 0)
		n--;
	n += 2;
	i = n;
	while (i-- > 1)
		msk = (msk << 1) + 1;
	*(*str)++ = ((wchar >> (6 * (n - 1))) + (msk << (8 - n)));
	while (--n > 0)
		*(*str)++ = ((wchar >> ((n - 1) * 6)) & 0x3F) + 0x80;
}

char			*wstr_to_str(int *wstr)
{
	char	*str;
	char	*curs;
	int		len;

	if (!wstr)
		return (NULL);
	len = ft_wstrlen(wstr);
	str = ft_strnew(len);
	curs = str;
	while (*wstr)
	{
		if (*wstr < 0x80)
			*curs++ = *wstr;
		else if (*wstr < 0x10FFFF)
			wchar_to_char(*wstr, &curs);
		else
			return (NULL);
		wstr++;
	}
	return (str);
}


int		main(void)
{
	wchar_t *test = L"≈ßΩ";
	char		*str;

	str = wstr_to_str(test);
	write(1, str, ft_strlen(str));
	free(str);
	return (0);
}