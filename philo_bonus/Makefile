NAME = philo_bonus

HDR = srcs/philo_bonus.h

SRCS = error_bonus.c fork_bonus.c free_bonus.c\
init_bonus.c main_bonus.c start_bonus.c \
thread_bonus.c utils_bonus.c

OBJS = ${addprefix srcs/,${SRCS:.c=.o}}

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIB = -lpthread

%.o: %.c ${HDR} Makefile
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIB}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
