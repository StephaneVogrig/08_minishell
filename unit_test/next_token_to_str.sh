# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    next_token_to_str.sh                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/24 16:15:01 by svogrig           #+#    #+#              #
#    Updated: 2024/05/24 16:47:33 by svogrig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC="	src/next_token_to_str_test.c
		../src/parsing/next_token_to_str.c
		../src/parsing/char.c
		../src/utils/str.c
	"

I_FLAG="-I../include/utils 
		-I../include/parsing 
		-I../libft/include 
		-Iinclude
	"

L_FLAG="../libft"

l_FLAG="ft"

cc $I_FLAG  $SRC "../libft/libft.a" -g -o next_token_to_str_test.exe

valgrind ./next_token_to_str_test.exe

