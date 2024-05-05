
SRC="main.c 
	../src/memory.c 
	../src/list_utils.c 
	../src/env_utils.c 
	../src/environment.c 
	../src/builtin_unset.c 
	../src/command.c 
	../src/redirection.c 
	../src/manage_node.c 
	../src/env_shlvl.c 
	src/env_shlvl_test.c 
	src/env_dup_test.c 
	src/env_get_test.c"

I_FLAG="-I../include -I../libft/include -Iinclude -g"

L_FLAG="../libft"

l_FLAG="ft"


cc $I_FLAG  $SRC "../libft/libft.a" -o unitest