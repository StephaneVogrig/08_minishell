# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    wildcard_bonus.sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 00:08:40 by smortemo          #+#    #+#              #
#    Updated: 2024/06/09 22:30:48 by svogrig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC="	src/wildcard_bonus_test.c
		../src/execution/wildcard_utils_bonus.c
		../src/execution/wildcard_bonus.c
	"

I_FLAG="-I../include/execution -I../include/parsing -I../libft/include -Iinclude"

L_FLAG="../libft"

l_FLAG="ft"

cc $I_FLAG  $SRC "../libft/libft.a" -g -o wildcard.exe

#gdb --tui wildcard.exe
./wildcard.exe
