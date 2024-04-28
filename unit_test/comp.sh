
SRC="main.c 
	../src/memory.c 
	../src/environment.c 
	src/env_dup_test.c 
	src/env_get_test.c"

I_FLAG="-I../include -I../libft/include -Iinclude -g"

L_FLAG="../libft"

l_FLAG="ft"


cc $I_FLAG  $SRC "../libft/libft.a" -o unitest