# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    wildcard_bonus.sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 00:08:40 by smortemo          #+#    #+#              #
#    Updated: 2024/06/06 02:04:47 by smortemo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC="	src/wildcard_bonus_test.c
		../src/execution/wildcard_bonus.c
	"

I_FLAG="-I../include/execution -I../include/parsing -I../libft/include -Iinclude"

L_FLAG="../libft"

l_FLAG="ft"

cc $I_FLAG  $SRC "../libft/libft.a" -g -o wildcard.exe

#gdb --tui wildcard.exe
./wildcard.exe
