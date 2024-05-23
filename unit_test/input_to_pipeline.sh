# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    input_to_pipeline.sh                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/05 22:23:47 by svogrig           #+#    #+#              #
#    Updated: 2024/05/23 11:13:01 by svogrig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC="	src/input_to_pipeline_test.c
		../src/input_to_pipeline.c
		../src/str.c
		../src/char.c
		../src/data/redirection.c
		../src/data/command.c
		../src/data/pipeline.c
		../src/token.c
		../src/parse.c
		../src/buffer/buff.c
		../src/buffer/buffadd.c
		../src/buffer/buffsave.c
		../src/expanse.c
		../src/argv.c
		../src/next_token_dequoted.c
		../src/environnement/environment.c
		../src/debug.c
	"

I_FLAG="-I../include -I../libft/include -Iinclude"

L_FLAG="../libft"

l_FLAG="ft"


cc $I_FLAG  $SRC "../libft/libft.a" -g -o test

./test
