# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/03 16:18:36 by jrasser           #+#    #+#              #
#    Updated: 2022/05/10 03:33:50 by jrasser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS 		= srcs/main.c \
			srcs/checker.c \
			srcs/get_args.c \
			srcs/time.c

OBJS 		= ${SRCS:.c=.o}
RM			= rm -f
NAME 		= philo
CC 			= gcc
CFLAGS		= -Wall -Wextra -g -fsanitize=address


${NAME}	:	${OBJS}
			gcc -o ${NAME} ${OBJS} -lpthread -D_REENTRANT ${CFLAGS}


all : ${NAME}

clean :
	${RM} ${OBJS}

fclean : clean
	${RM} ${NAME}

re : fclean all

.PHONY:	all clean fclean re
