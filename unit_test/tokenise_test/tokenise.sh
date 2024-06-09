# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tokenise.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 15:18:48 by svogrig           #+#    #+#              #
#    Updated: 2024/06/09 17:36:38 by svogrig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

SRC="main.c
	../../src/utils/str.c
	../../src/parsing/char.c 
	../../src/parsing/syntax_error.c 
	../../src/parsing/syntax_error_utils.c 
	../../src/parsing/tokenise.c
	../../src/parsing/tokenise_parse.c
	../../src/parsing/tokenlist.c"

I_FLAG="-I../../include/utils -I../../include/parsing -I../../libft/include -Iinclude -g"

L_FLAG="../../libft"

l_FLAG="ft"

cc $I_FLAG  $SRC "../../libft/libft.a" -g -o tokenise

./tokenise