NAME	= libft.a

SRCS =	ft_atoi.c \
	ft_atol.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strjoin_free.c \
	ft_strlcat.c \
	ft_strcpy.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_get_next_line.c \
	ft_print_char.c \
	ft_putstr.c \
	ft_print_nbr_base.c \
	ft_printf.c \
	ft_free_the_tab.c \
	ft_str_isalpha.c 


OBJS	= ${SRCS:.c=.o}

CFLAGS	= -Wall -Werror -Wextra

RM	= rm -f

AR	= ar

${NAME}:    ${OBJS}
	ar -csr ${NAME} ${OBJS}

${OBJS}: ${SRCS} libft.h

all:	${NAME}

clean:	
	${RM} ${OBJS}

fclean: clean 
	${RM} ${NAME}

re:		
	${MAKE} fclean
	${MAKE} all
