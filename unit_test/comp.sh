
SRC="main.c 
	../src/utils/memory.c 
	../src/environment/env_utils.c 
	../src/environment/environment.c 
	../src/builtins/builtin_unset.c 
	../src/data/command.c 
	../src/data/redirection.c 
	../src/environment/env_node.c 
	../src/environment/env_node2.c 
	../src/environment/env_shlvl.c
	../src/execution/heredoc.c 
	../src/utils/str.c 
	src/env_shlvl_test.c 
	src/env_dup_test.c 
	src/env_get_test.c
	src/heredoc_test.c"

I_FLAG="-I../include -I../libft/include -Iinclude -g" 

L_FLAG="../libft"

l_FLAG="ft"


cc $I_FLAG  $SRC "../libft/libft.a" -o unitest