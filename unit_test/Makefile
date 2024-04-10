# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/10 18:58:49 by smortemo          #+#    #+#              #
#    Updated: 2024/04/10 20:44:07 by smortemo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	unitest
NAME_DEBUG		:=	$(NAME)_debug
NAME_SAN		:=	$(NAME)_sanitize

# unit tests ------------------------------------------------------------------#

DIR_SRC			:=	src

SRC				:=	main.c \
					env_dup_test.c
					
SRC				:=	$(SRC:%=$(DIR_SRC)/%)

# minishell -------------------------------------------------------------------#

DIR_MS			:= ../src

SRC_MS			:=	environment.c

SRC_MS			:=	$(SRC_MS:%=$(DIR_MS)/%)

# includes --------------------------------------------------------------------#

DIR_INC			:=	../libft/include \
				../include
I_FLAG			:=	$(addprefix -I,$(DIR_INC)) -MMD -MP
				
# library ---------------------------------------------------------------------#

LIBFT_DIR		:=	../libft

L_FLAG			:=	$(LIBFT_DIR)
L_FLAG			:=	$(addprefix -L,$(L_FLAG))

l_FLAG			:=	ft readline
l_FLAG			:=	$(addprefix -l,$(l_FLAG))

# objects ---------------------------------------------------------------------#

DIR_BUILD		:=	.build
OBJ				:=	$(SRC:%.c=$(DIR_BUILD)/%.o)
OBJ_MS			:=	$(SRC_MS:%.c=$(DIR_BUILD)/%.o)
OBJ_DEBUG		:=	$(SRC:$(DIR_SRC)/%.c=$(DIR_BUILD)/debug/%.o)
OBJ_SAN			:=	$(SRC:$(DIR_SRC)/%.c=$(DIR_BUILD)/sanitize/%.o)

DEPS			:=	$(OBJ:.o=.d) $(OBJ_MS:.o=.d) $(OBJ_SAN:.o=.d) $(OBJ_BONUS:.o=.d)

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

#------------------------------------------------------------------------------#
# rules                                                                        #
#------------------------------------------------------------------------------#

all: 
	@$(MAKE) -j makeall

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(DIR_BUILD)

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(DIR_BUILD)
	@rm -f	$(NAME) \
			$(NAME_DEBUG) \
			$(NAME_SAN)

re: fclean
	@$(MAKE) -j makeall

run: all
	- ./$(NAME) $(RUNARGS)

valgrind: debug
	- valgrind $(VAL_FLAGS) $(VAL_FLAGS_C) $(VAL_SUPPR) ./$(NAME_DEBUG) $(RUNARGS)

sanitize:
	@$(MAKE) -j makesanitize
	- ./$(NAME_SAN) $(RUNARGS)


makeall:		$(NAME)
makedebug:		$(NAME_DEBUG)
makesanitize:	$(NAME_SAN)

#------------------------------------------------------------------------------#
# compilation                                                                  #
#------------------------------------------------------------------------------#

$(DIR_BUILD)/%.o: %.c
	@mkdir -p $(@D)
	@printf "\033[2K\rcompiling: %s" $@
	@$(CC) $(CC_FLAGS) $(I_FLAG) -c $< -o $@

$(DIR_BUILD)/debug/%.o: $(DIR_SRC)/%.c
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
	@$(MAKE) -j -C $(LIBFT_DIR)
	@$(CC) $(CC_FLAGS) $(OBJ) $(L_FLAG) $(l_FLAG) -o $(NAME)
	@printf "\033[2K\rcreated: %s\n" $@

$(NAME_DEBUG): $(OBJ_DEBUG)
	@$(MAKE) -j -C $(LIBFT_DIR)
	@$(CC) $(CC_FLAGS) $(OBJ_DEBUG) $(L_FLAG) $(l_FLAG) -g -o $(NAME_DEBUG)
	$(info created : $(NAME_DEBUG))

$(NAME_SAN): $(OBJ_SAN)
	@$(MAKE) -j -C $(LIBFT_DIR)
	@$(CC) $(OBJ_SAN) $(L_FLAG) $(l_FLAG) $(SAN_FLAGS) -o $(NAME_SAN)
	$(info created : $(NAME_SAN))
	
#------------------------------------------------------------------------------#
# specifications                                                               #
#------------------------------------------------------------------------------#

.PHONY: all \
		clean \
		fclean \
		re \
		run \
		debug \
		valgrind \
		sanitize \
		makeall \
		makedebug \
		makesanitize