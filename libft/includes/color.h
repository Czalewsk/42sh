/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 21:45:26 by bviala            #+#    #+#             */
/*   Updated: 2018/01/10 21:46:44 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __COLOR_H
# define __COLOR_H

/*
 * ** SET ALL DEFAULT
 * */

# define C_DEFAULT	"\033[m"

/*
 * ** TEXT COLOR
 * */

# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENDA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"

/*
 * ** ANSI TEXT COLOR
 * */

# define X_BLACK	"\033[1;30m"
# define X_RED		"\033[1;31m"
# define X_GREEN	"\033[1;32m"
# define X_YELLOW	"\033[1;33m"
# define X_BLUE		"\033[1;34m"
# define X_MAGENDA	"\033[1;35m"
# define X_CYAN		"\033[1;36m"
# define X_WHITE	"\033[1;37m"

/*
 * ** FONT COLOR
 * */

# define F_BLACK	"\033[40m"
# define F_RED		"\033[41m"
# define F_GREEN	"\033[42m"
# define F_YELLOW	"\033[43m"
# define F_BLUE		"\033[44m"
# define F_MAGENDA	"\033[45m"
# define F_CYAN		"\033[46m"
# define F_WHITE	"\033[47m"

/*
 * ** TEXT EDIT
 * */

# define T_BOLD			"\033[1m"
# define T_ITALIC		"\033[3m"
# define T_UNDERLINED	"\033[4m"
# define T_INVERTED		"\033[7m"

#endif
