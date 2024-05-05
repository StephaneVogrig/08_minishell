
SRC="main.c 
	../src/memory.c 
	../src/environnement/list_utils.c 
	../src/environnement/env_utils.c 
	../src/environnement/environment.c 
	../src/builtins/builtin_unset.c 
	../src/data/command.c 
	../src/data/redirection.c 
	../src/environnement/manage_node.c 
	../src/environnement/env_shlvl.c
	../src/heredoc.c 
	src/env_shlvl_test.c 
	src/env_dup_test.c 
	src/env_get_test.c
	src/heredoc_test.c"

I_FLAG="-I../include -I../libft/include -Iinclude -g" 

L_FLAG="../libft"

l_FLAG="ft"


cc $I_FLAG  $SRC "../libft/libft.a" -o unitest