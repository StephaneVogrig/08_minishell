# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 16:51:41 by svogrig           #+#    #+#              #
#    Updated: 2024/06/19 20:06:47 by svogrig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	minishell
NAME_BONUS		:=	$(NAME)_bonus
NAME_DEBUG		:=	$(NAME)_debug
NAME_DEBUG_B	:=	$(NAME)_bonusdebug
NAME_SAN		:=	$(NAME)_sanitize
NAME_SANB		:=	$(NAME)_bonussanitize

# sources ---------------------------------------------------------------------#

DIR_SRC			:=	src

SRC				:=	main.c \
					buffer/buff.c \
					buffer/buffadd.c \
					buffer/buffsave.c \
					builtins/builtin_cd.c \
					builtins/builtin_echo.c \
					builtins/builtin_env.c \
					builtins/builtin_exit.c \
					builtins/builtin_exit_utils.c \
					builtins/builtin_export_alone.c \
					builtins/builtin_export.c \
					builtins/builtin_unset.c \
					builtins/builtin_pwd.c \
					data/argv.c \
					data/command.c \
					data/pipeline.c \
					data/redirection.c \
					environment/env_get.c \
					environment/env_node.c \
					environment/env_node2.c \
					environment/env_pwd.c \
					environment/env_shlvl.c \
					environment/env_utils.c \
					environment/environment.c \
					environment/envp.c \
					environment/tilde.c \
					execution/argv_expand.c \
					execution/cmd_path.c \
					execution/exec_builtin.c \
					execution/exec_cmd.c \
					execution/expanse.c \
					execution/heredoc_utils.c \
					execution/heredoc_expand.c \
					execution/pipeline_wait.c \
					execution/process_utils.c \
					execution/exec_pipeline.c \
					execution/exec_redir.c \
					parsing/next_token_limiter.c \
					parsing/next_token_to_str.c \
					parsing/parse_utils.c \
					parsing/syntax_error_utils.c \
					shell/exit_status.c \
					shell/prompt.c \
					shell/shell_mode.c \
					utils/exit.c \
					utils/memory.c \
					utils/mini_readline.c \
					utils/mini_strtol.c \
					utils/pipe.c \
					utils/signal_handler.c \
					utils/str.c

SRC_MAND		:=	$(SRC) \
					execution/exec_input.c \
					execution/exec_alone.c \
					execution/expand_and_dequote.c \
					execution/expand_utils.c \
					execution/heredoc.c \
					execution/process.c \
					parsing/char.c \
					parsing/input_to_pipeline.c \
					parsing/parse.c \
					parsing/syntax_error.c \
					utils/minish_free.c

SRC_MAND		:=	$(SRC_MAND:%=$(DIR_SRC)/%)

# sources bonus ---------------------------------------------------------------#

SRC_BONUS		:=	$(SRC) \
					bonus/data/pipelist_bonus.c \
					bonus/execution/exec_input_bonus.c \
					bonus/execution/exec_alone_bonus.c \
					bonus/execution/exec_pipelist_bonus.c \
					bonus/execution/expand_and_dequote_bonus.c \
					bonus/execution/expand_and_dequote_utils_bonus.c \
					bonus/execution/expand_utils_bonus.c \
					bonus/execution/heredoc_bonus.c \
					bonus/execution/process_bonus.c \
					bonus/execution/tmpdata_bonus.c \
					bonus/execution/wildcard_bonus.c \
					bonus/execution/wildcard_utils_bonus.c \
					bonus/parsing/char_bonus.c \
					bonus/parsing/input_to_pipelist_bonus.c \
					bonus/parsing/parse_bonus.c \
					bonus/parsing/syntax_error_bonus.c \
					bonus/parsing/syntax_error_utils_bonus.c \
					bonus/parsing/tokenise_parse_bonus.c \
					bonus/parsing/tokenise_bonus.c \
					bonus/parsing/tokenlist_bonus.c \
					bonus/utils/minish_free_bonus.c \
					bonus/utils/sortlist_bonus.c

SRC_BONUS		:=	$(SRC_BONUS:%=$(DIR_SRC)/%)

# includes --------------------------------------------------------------------#

DIR_INC			:=	libft/include \
					include \
					include/buff \
					include/builtins \
					include/data \
					include/environment \
					include/execution \
					include/parsing \
					include/utils \
					include/shell \
					include/bonus/data \
					include/bonus/execution \
					include/bonus/parsing \
					include/bonus/utils

I_FLAG			:=	$(addprefix -I,$(DIR_INC)) -MMD -MP
				
# library ---------------------------------------------------------------------#

LIB_FT			:=	libft/libf.a

L_FLAG			:=	libft
L_FLAG			:=	$(addprefix -L,$(L_FLAG))

l_FLAG			:=	ft readline
l_FLAG			:=	$(addprefix -l,$(l_FLAG))

# objects ---------------------------------------------------------------------#

DIR_BUILD		:=	.build
OBJ_MAND		:=	$(SRC_MAND:$(DIR_SRC)/%.c=$(DIR_BUILD)/%.o)
OBJ_BONUS		:=	$(SRC_BONUS:$(DIR_SRC)/%.c=$(DIR_BUILD)/%.o)
OBJ_DEBUG		:=	$(SRC_MAND:$(DIR_SRC)/%.c=$(DIR_BUILD)/debug/%.o)
OBJ_DEBUGB		:=	$(SRC_BONUS:$(DIR_SRC)/%.c=$(DIR_BUILD)/debugbonus/%.o)
OBJ_SAN			:=	$(SRC_MAND:$(DIR_SRC)/%.c=$(DIR_BUILD)/sanitize/%.o)
OBJ_SANB		:=	$(SRC_BONUS:$(Dfd[1]IR_SRC)/%.c=$(DIR_BUILD)/sanitize/%.o)

DEPS			:=	$(OBJ:.o=.d) $(OBJ_SAN:.o=.d) $(OBJ_BONUS:.o=.d)

# compilation -----------------------------------------------------------------#

CC				:=	cc
CC_FLAGS		:=	-Wall -Wextra -Werror

# valgrind --------------------------------------------------------------------#

VAL_FLAGS		:=	--leak-check=full --track-origins=yes --track-fds=yes
VAL_FLAGS_C		:=	--show-leak-kinds=all --trace-children=yes
VAL_SUPPR		:= 	--suppressions=readline.suppr

# sanitize --------------------------------------------------------------------#

SAN_FLAGS		:=	-fsanitize=address

# make ------------------------------------------------------------------------#

MAKEFLAGS		+=	--no-print-directory

# run -------------------------------------------------------------------------#

RUNARGS			:=
RUNARGS_BONUS	:=

#------------------------------------------------------------------------------#
# rules                                                                        #
#------------------------------------------------------------------------------#

all: 
	@$(MAKE) -j makeall

clean:
	@$(MAKE) -C libft clean
	@rm -rf $(DIR_BUILD)

fclean:
	@$(MAKE) -C libft fclean
	@rm -rf $(DIR_BUILD)
	@rm -f	$(NAME) \
			$(NAME_BONUS) \
			$(NAME_DEBUG) \
			$(NAME_DEBUG_B) \
			$(NAME_SAN)  \
			$(NAME_SANB)

re: fclean
	@$(MAKE) -j makeall

bonus:
	@$(MAKE) -j makebonus

rebonus: fclean bonus

run: all
	- ./$(NAME) $(RUNARGS)

runbonus: bonus
	- ./$(NAME_BONUS) $(RUNARGS_BONUS)

debug:
	@$(MAKE) -j makedebug

debugbonus:
	@$(MAKE) -j makedebug_b

valgrind: debug
	- valgrind $(VAL_FLAGS) $(VAL_FLAGS_C) $(VAL_SUPPR) ./$(NAME_DEBUG) $(RUNARGS)

valgrindbonus: debugbonus
	- valgrind $(VAL_FLAGS) $(VAL_FLAGS_C) $(VAL_SUPPR) ./$(NAME_DEBUG_B) $(RUNARGS_BONUS)

sanitize:
	@$(MAKE) -j makesanitize
	- ./$(NAME_SAN) $(RUNARGS)

sanitizebonus:
	@$(MAKE) -j makesanitize_b
	- ./$(NAME_SANB) $(RUNARGS)

makeall:		$(NAME)
makebonus:		$(NAME_BONUS)
makedebug:		$(NAME_DEBUG)
makedebug_b:	$(NAME_DEBUG_B)
makesanitize:	$(NAME_SAN)
makesanitize_b:	$(NAME_SANB)

#------------------------------------------------------------------------------#
# compilation                                                                  #
#------------------------------------------------------------------------------#

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	@printf "\033[2K\rcompiling: %s" $@
	@$(CC) $(CC_FLAGS) $(I_FLAG) -c $< -o $@

$(DIR_BUILD)/debug/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CC_FLAGS) $(I_FLAG) $(DEBUG_FLAGS) -g -c $< -o $@
	$(info created : $@)

$(DIR_BUILD)/debugbonus/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CC_FLAGS) $(I_FLAG) $(DEBUG_FLAGS) -g -c $< -o $@
	$(info created : $@)

$(DIR_BUILD)/sanitize/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CC_FLAGS) $(I_FLAG) $(SAN_FLAGS) -c $< -o $@
	$(info created : $@)

-include $(DEPS)

#------------------------------------------------------------------------------#
# linkage                                                                      #
#------------------------------------------------------------------------------#

$(NAME): $(OBJ_MAND)
	@$(MAKE) -j -C libft
	@$(CC) $(CC_FLAGS) $(OBJ_MAND) $(L_FLAG) $(l_FLAG) -o $(NAME)
	@printf "\033[2K\rcreated: %s\n" $@

$(NAME_BONUS): $(OBJ_BONUS)
	@$(MAKE) -j -C libft
	@$(CC) $(CC_FLAGS) $(OBJ_BONUS) $(L_FLAG) $(l_FLAG) -o $(NAME)
	@printf "\033[2K\rcreated: %s\n" $@

$(NAME_DEBUG): $(OBJ_DEBUG)
	@$(MAKE) -j -C libft
	@$(CC) $(CC_FLAGS) $(OBJ_DEBUG) $(L_FLAG) $(l_FLAG) -g -o $(NAME_DEBUG)
	$(info created : $(NAME_DEBUG))

$(NAME_DEBUG_B): $(OBJ_DEBUGB)
	@$(MAKE) -j -C libft
	@$(CC) $(CC_FLAGS) $(OBJ_DEBUGB) $(L_FLAG) $(l_FLAG) -g -o $(NAME_DEBUG_B)
	$(info created : $(NAME_DEBUG_B))

$(NAME_SAN): $(OBJ_SAN)
	@$(MAKE) -j -C libft
	@$(CC) $(OBJ_SAN) $(L_FLAG) $(l_FLAG) $(SAN_FLAGS) -o $(NAME_SAN)
	$(info created : $(NAME_SAN))

$(NAME_SANB): $(OBJ_SANB)
	@$(MAKE) -j -C libft
	@$(CC) $(OBJ_SANB) $(L_FLAG) $(l_FLAG) $(SAN_FLAGS) -o $(NAME_SANB)
	$(info created : $(NAME_SANB))

#------------------------------------------------------------------------------#
# specifications                                                               #
#------------------------------------------------------------------------------#

.PHONY: all \
		clean \
		fclean \
		bonus \
		re \
		rebonus \
		run \
		runbonus \
		debug \
		debugbonus \
		valgrind \
		sanitize \
		sanitizebonus \
		makeall \
		makebonus \
		makedebug \
		makedebug_b \
		makesanitize \
		makesanitize_b
