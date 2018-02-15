# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thugo <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/28 14:48:37 by thugo             #+#    #+#              #
#    Updated: 2017/04/05 07:21:30 by thugo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@make -C framework
	@make -C tests

clean:
	@make -C framework clean
	@make -C tests clean

fclean:
	@make -C framework fclean
	@make -C tests fclean

re: fclean all

run: all
	@make -C tests run

.PHONY: all clean fclean re run
