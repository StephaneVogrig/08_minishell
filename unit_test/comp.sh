
SRC="main.c 
	../src/builtin_unset.c 
	../src/builtin_export.c 
	../src/builtin_env.c 
	../src/memory.c 
	../src/environment.c 
	src/env_dup_test.c 
	src/env_get_test.c 
	src/builtin_unset_test.c 
	src/builtin_export_test.c 
	src/builtin_export_alone_test.c 
	src/builtin_env_test.c "

I_FLAG="-I../include -I../libft/include -Iinclude -g"

L_FLAG="../libft"

l_FLAG="ft"


cc $I_FLAG  $SRC "../libft/libft.a" -o unitest