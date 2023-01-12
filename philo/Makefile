NAME = philo

HDR = srcs/philo.h

SRCS = main.c utils.c error.c init.c start.c philo.c

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
