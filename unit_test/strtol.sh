# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    strtol.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 11:11:43 by svogrig           #+#    #+#              #
#    Updated: 2024/05/23 11:38:37 by svogrig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC="	src/strtol_test.c
		../src/utils/mini_strtol.c
	"

I_FLAG="-I../include/utils -I../include/parsing -I../libft/include -Iinclude"

L_FLAG="../libft"

l_FLAG="ft"

cc $I_FLAG  $SRC "../libft/libft.a" -g -o strtol.exe

./strtol.exe
