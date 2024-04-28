#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stephane <stephane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 16:51:41 by svogrig           #+#    #+#              #
#    Updated: 2024/04/27 16:24:14 by stephane         ###   ########.fr        #
#                                                                              #
#******************************************************************************#


NAME			:=	minishell
NAME_BONUS		:=	$(NAME)_bonus
NAME_DEBUG		:=	$(NAME)_debug
NAME_DEBUG_B	:=	$(NAME)_bonusdebug
NAME_SAN		:=	$(NAME)_sanitize
NAME_SANB		:=	$(NAME)_bonussanitize

# sources ---------------------------------------------------------------------#

DIR_SRC			:=	src
#SRC				=	$(shell find ./src/ -name *.c)
SRC				:=	main.c \
					buff.c \
					buffadd.c \
					buffsave.c \
					command.c \
					cmd_path.c \
					environment.c \
					exec_input.c \
					exec_cmd.c \
					exit.c \
					expanse.c \
					input_to_pipeline.c \
					memory.c \
					pipeline.c \
					heredoc_bonus.c \
					parse.c \
					pipe.c \
					process.c \
					redirection.c \
					signal_handler.c \
					str.c \
					strlink.c \
					token.c \
					debug.c \
					wait.c 

SRC				:=	$(SRC:%=$(DIR_SRC)/%)

# sources bonus ---------------------------------------------------------------#

SRC_BONUS		:=	$(SRC)

#SRC_BONUS		:=	$(SRC_BONUS:%=$(DIR_SRC)/%)

# includes --------------------------------------------------------------------#

DIR_INC			:=	libft/include \
				include
I_FLAG			:=	$(addprefix -I,$(DIR_INC)) -MMD -MP
				
# library ---------------------------------------------------------------------#

LIB_FT			:=	libft/libf.a

L_FLAG			:=	libft
L_FLAG			:=	$(addprefix -L,$(L_FLAG))

l_FLAG			:=	ft readline
l_FLAG			:=	$(addprefix -l,$(l_FLAG))

# objects ---------------------------------------------------------------------#

DIR_BUILD		:=	.build
OBJ				:=	$(SRC:$(DIR_SRC)/%.c=$(DIR_BUILD)/%.o)

# objects ---------------------------------------------------------------------#

DIR_BUILD		:=	.build
OBJ				:=	$(SRC:$(DIR_SRC)/%.c=$(DIR_BUILD)/%.o)
OBJ_BONUS		:=	$(SRC_BONUS:$(DIR_SRC)/%.c=$(DIR_BUILD)/%.o)
OBJ_DEBUG		:=	$(SRC:$(DIR_SRC)/%.c=$(DIR_BUILD)/debug/%.o)
OBJ_DEBUGB		:=	$(SRC_BONUS:$(DIR_SRC)/%.c=$(DIR_BUILD)/debugbonus/%.o)
OBJ_SAN			:=	$(SRC:$(DIR_SRC)/%.c=$(DIR_BUILD)/sanitize/%.o)
OBJ_SANB		:=	$(SRC_BONUS:$(DIR_SRC)/%.c=$(DIR_BUILD)/sanitize/%.o)

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
	- valgrind $(VAL_FLAGS) $(VAL_FLAGS_C) $(VAL_SUPPR) ./$(NAME_DEBUG) $(RUNARGS_BONUS)

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
	@$(CC) $(CC_FLAGS) $(I_FLAG) $(DEBUG_FLAGS) -c $< -o $@
	$(info created : $@)

$(DIR_BUILD)/debugbonus/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CC_FLAGS) $(I_FLAG) $(DEBUG_FLAGS) -c $< -o $@
	$(info created : $@)

$(DIR_BUILD)/sanitize/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CC_FLAGS) $(I_FLAG) $(SAN_FLAGS) -c $< -o $@
	$(info created : $@)

-include $(DEPS)

#------------------------------------------------------------------------------#
# linkage                                                                      #
#------------------------------------------------------------------------------#

$(NAME): $(OBJ)
	@$(MAKE) -j -C libft
	@$(CC) $(CC_FLAGS) $(OBJ) $(L_FLAG) $(l_FLAG) -o $(NAME)
	@printf "\033[2K\rcreated: %s\n" $@

$(NAME_BONUS): $(OBJ_BONUS)
	@$(MAKE) -j -C libft
	@$(CC) $(CC_FLAGS) $(OBJ_BONUS) $(L_FLAG) $(l_FLAG) -o $(NAME_BONUS)
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