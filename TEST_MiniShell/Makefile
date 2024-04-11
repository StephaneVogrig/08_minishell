NAME = test

SRCS = test_create_env_built_export_unset.c

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

CC = cc

CFLAGS =  -Wall -Wextra -Werror -g 

RM = rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	@${MAKE} -C ./libft
	@${CC} ${CFLAGS} ${OBJS} ./libft/libft.a -lreadline -o ${NAME}

signal:
	@${MAKE} -C ./libft
	@${CC} ${CFLAGS} test_readline_history_with_signal_V2.c ./libft/libft.a -lreadline -o ${NAME}

clean: 
	@${MAKE} -C ./libft fclean
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
